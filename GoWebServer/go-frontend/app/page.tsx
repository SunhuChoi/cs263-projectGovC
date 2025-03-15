"use client";

import { useState, useEffect, useRef } from "react";
import {
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@/components/ui/tabs";
import {
  Description,
  Dialog,
  DialogPanel,
  DialogTitle,
  Menu,
  MenuItem,
  MenuItems,
} from "@headlessui/react";
import { Button } from "@/components/ui/button";
import {
  RefreshCcw,
  Check,
  X,
  ChartColumn,
  Smile,
  Meh,
  Frown,
} from "lucide-react";

interface MemStats {
  Alloc: number;
  TotalAlloc: number;
  Sys: number;
  Mallocs: number;
  Frees: number;
  LiveObjects: number;
  PauseTotalNs: number;
  NumGC: number;
  HeapSys: number;
  HeapIdle: number;
  HeapInuse: number;
  StackInuse: number;
  StackSys: number;
  GCSys: number;
  NextGC: number;
  NumGoR: number;
}

export default function Home() {
  const [memStats, setMemStats] = useState<MemStats | null>(null);
  const [connected, setConnected] = useState(false);
  const [lastUpdated, setLastUpdated] = useState<Date | null>(null);
  const wsRef = useRef<WebSocket | null>(null);
  const [goAlert, setGoAlert] = useState(false);
  const [backgroundColor, setBackgroundColor] = useState(false);
  const [openModal, setOpenModal] = useState(false);
  const [triggerReconnect, setTriggerReconnect] = useState(false);
  const [allocBackgroundColor, setAllocBackgroundColor] = useState(false);
  const [gCCountBgColor, setgCCountBgColor] = useState(true);
  const [gcCount, setGcCount] = useState(0);
  const [stackCount, setStackCount] = useState(false);
  const [statusButtonWindow, setStatusButtonWindow] = useState(false);
  //allocBackgroundColor, stackCount, backgroundColor

  useEffect(() => {
    if (wsRef.current) {
      wsRef.current.close();
    }

    const ws = new WebSocket("ws://localhost:8080/ws");
    wsRef.current = ws;

    ws.addEventListener("open", () => {
      console.log("Connected to WebSocket");
      setConnected(true);
    });

    ws.addEventListener("message", (event) => {
      try {
        const data = JSON.parse(event.data);
        setMemStats(data);
        setLastUpdated(new Date());
      } catch {
        if (event.data == "Nice!") {
          console.log("Nice");
        }
      }
    });

    ws.addEventListener("close", () => {
      console.log("Disconnected from WebSocket");
      if (wsRef.current != null && wsRef.current.readyState === WebSocket.OPEN)
        setConnected(true);
      else {
        setConnected(false);
        setGcCount(0);
      }
    });

    ws.addEventListener("error", (event) => {
      console.error("WebSocket error:", event);
      if (wsRef.current != null && wsRef.current.readyState === WebSocket.OPEN)
        setConnected(true);
      else {
        setConnected(false);
        setGcCount(0);
      }
    });

    return () => {
      ws.close();
    };
  }, [triggerReconnect]);

  useEffect(() => {
    if (
      memStats != null &&
      memStats.NumGoR >= 10 &&
      memStats.NumGoR != 4294967295
    ) {
      setBackgroundColor(true);
      reveal();
    } else if (
      memStats != null &&
      memStats.NumGoR < 10 &&
      memStats.NumGoR != 4294967295
    ) {
      setBackgroundColor(false);
      close();
    }

    if (memStats != null && memStats.Alloc >= 10485760) {
      setAllocBackgroundColor(true);
    } else if (memStats != null && memStats.Alloc < 10485760) {
      setAllocBackgroundColor(false);
    }

    console.log(memStats?.StackInuse);
    if (memStats != null && memStats.StackInuse > 4194304) {
      if (wsRef.current != null) wsRef.current.send("Stack Remove");
      reveal();
      setStackCount(true);
    } else if (memStats != null && memStats.StackInuse < 4194304) {
      setStackCount(false);
    }
  }, [memStats]);

  useEffect(() => {
    const gcCountID = setInterval(() => {
      if (memStats != null && memStats.NumGC > gcCount) {
        setgCCountBgColor(true);
        setGcCount(memStats.NumGC);
      } else if (memStats != null) {
        setgCCountBgColor(false);
      }
    }, 500);
    return () => {
      clearInterval(gcCountID);
    };
  });

  function reconnect() {
    console.log("Connecting to WebSocket...");
    if (triggerReconnect === true) {
      console.log("Entered!");
      setTriggerReconnect(false);
    } else {
      setTriggerReconnect(true);
    }
  }
  function reveal() {
    setOpenModal(true);
  }

  function close() {
    setOpenModal(false);
  }

  const yesButtonClicked = () => {
    if (wsRef.current != null) wsRef.current.send("Add");
  };

  const noButtonClicked = () => {
    if (wsRef.current != null) wsRef.current.send("Remove");
  };

  const addButtonClicked = () => {
    if (wsRef.current != null) wsRef.current.send("Stack");
  };

  const stackRemoveButtonClicked = () => {
    if (wsRef.current != null) wsRef.current.send("Stack Remove");
  };

  const addHeapButtonClicked = () => {
    if (wsRef.current != null) wsRef.current.send("Heap");
  };

  const heapRemoveButtonClicked = () => {
    if (wsRef.current != null) wsRef.current.send("Heap Remove");
  };

  const openStatusButtonClicked = () => {
    setStatusButtonWindow(true);
  };

  const closeStatusButtonClicked = () => {
    setStatusButtonWindow(false);
  };

  const formatBytes = (bytes: number) => {
    if (bytes === 0) return "0 Bytes";
    const k = 1024;
    const sizes = ["Bytes", "KB", "MB", "GB"];
    const i = Math.floor(Math.log(bytes) / Math.log(k));
    return (
      Number.parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + " " + sizes[i]
    );
  };

  const formatNanoseconds = (ns: number) => {
    if (ns < 1000) return `${ns} ns`;
    if (ns < 1000000) return `${(ns / 1000).toFixed(3)} µs`;
    if (ns < 1000000000) return `${(ns / 1000000).toFixed(3)} ms`;
    return `${(ns / 1000000000).toFixed(3)} s`;
  };

  return (
    <main className="container mx-auto p-4 min-h-screen">
      <div className="flex justify-between items-center mb-4">
        <div className="flex items-center rounded-md bg-black p-4 -mt-2">
          <ChartColumn className="text-white" />
          <h1 className="text-3xl text-white font-bold">
            Go Runtime Memory Statistics
          </h1>
        </div>
        <div className="flex items-center gap-2 -mt-10">
          <div
            className={`flex items-center gap-1 px-3 py-1 rounded-full text-sm ${
              connected
                ? "bg-green-100 text-green-800"
                : "bg-red-100 text-red-800"
            }`}
          >
            {connected ? <Check /> : <X />}
            {connected ? "Connected" : "Disconnected"}
          </div>
          <Button onClick={reconnect} className="flex items-center gap-2">
            <RefreshCcw className="h-4 w-4" />
            Reconnect
          </Button>
          <Menu>
            <Button
              className={`${
                backgroundColor && allocBackgroundColor && stackCount
                  ? "bg-red-100 text-red-800"
                  : backgroundColor || allocBackgroundColor || stackCount
                  ? "bg-yellow-100 text-yellow-800"
                  : "bg-green-100 text-green-800"
              }`}
              onClick={openStatusButtonClicked}
              disabled={!connected}
            >
              {backgroundColor && allocBackgroundColor && stackCount ? (
                <Frown />
              ) : backgroundColor || allocBackgroundColor || stackCount ? (
                <Meh />
              ) : (
                <Smile />
              )}
              Status
            </Button>
          </Menu>
        </div>
      </div>
      {lastUpdated && (
        <div className="text-sm text-muted-foreground mb-4">
          Last updated: {lastUpdated.toLocaleTimeString()}
        </div>
      )}
      {memStats && (
        <Tabs defaultValue="overview">
          <TabsContent value="overview">
            <div className="text-3xl font-bold pb-4">Menu</div>
            <div className="grid grid-cols-4 gap-4 mb-4">
              <Card>
                <CardHeader>
                  <CardTitle className="text-center font-bold">
                    Go Routine Module
                  </CardTitle>
                  <CardDescription className="text-center">
                    Create or Finish a Go Routine? (Has to be made from this
                    module)
                  </CardDescription>
                </CardHeader>
                <CardContent className="flex justify-center items-center space-x-5">
                  <Button
                    onClick={yesButtonClicked}
                    className="bg-green-100 text-green-800"
                  >
                    Add
                  </Button>
                  <Button
                    onClick={noButtonClicked}
                    className="bg-red-100 text-red-800"
                  >
                    Remove
                  </Button>
                </CardContent>
              </Card>
              <Card>
                <CardHeader>
                  <CardTitle className="text-center font-bold">
                    Stack Allocator Module
                  </CardTitle>
                  <CardDescription className="text-center">
                    Add or remove from stack?
                  </CardDescription>
                </CardHeader>
                <CardContent className="flex justify-center items-center space-x-5">
                  <Button
                    onClick={addButtonClicked}
                    className="bg-green-100 text-green-800"
                  >
                    Add
                  </Button>
                  <Button
                    onClick={stackRemoveButtonClicked}
                    className="bg-red-100 text-red-800"
                  >
                    Remove
                  </Button>
                </CardContent>
              </Card>
              <Card>
                <CardHeader>
                  <CardTitle className="text-center font-bold">
                    Heap Allocator Module
                  </CardTitle>
                  <CardDescription className="text-center">
                    Add or remove from heap?
                  </CardDescription>
                </CardHeader>
                <CardContent className="flex justify-center items-center space-x-5">
                  <Button
                    onClick={addHeapButtonClicked}
                    className="bg-green-100 text-green-800"
                  >
                    Add
                  </Button>
                  <Button
                    onClick={heapRemoveButtonClicked}
                    className="bg-red-100 text-red-800"
                  >
                    Remove
                  </Button>
                </CardContent>
              </Card>
            </div>
            <div className="text-3xl font-bold pb-3">Stats</div>
            <div className="grid grid-cols-4 gap-4 mb-6">
              <Card
                className={`${
                  allocBackgroundColor ? "bg-red-100 text-red-800" : ""
                }`}
              >
                <CardHeader className="pb-2">
                  <CardTitle>Allocated Memory</CardTitle>
                  <CardDescription>Currently in use</CardDescription>
                </CardHeader>
                <CardContent>
                  <p className="text-3xl font-bold">
                    {formatBytes(memStats.Alloc)}
                  </p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>System Memory</CardTitle>
                  <CardDescription>Total from OS</CardDescription>
                </CardHeader>
                <CardContent>
                  <p className="text-3xl font-bold">
                    {formatBytes(memStats.Sys)}
                  </p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>Live Objects</CardTitle>
                  <CardDescription>Mallocs - Frees</CardDescription>
                </CardHeader>
                <CardContent>
                  <p className="text-3xl font-bold">
                    {memStats.Mallocs - memStats.Frees}
                  </p>
                </CardContent>
              </Card>
              <Card
                className={`${
                  backgroundColor ? "bg-red-100 text-red-800" : ""
                }`}
              >
                <CardHeader className="pb-2">
                  <CardTitle>Number of Active GoRoutines</CardTitle>
                  <CardDescription>Total Alive</CardDescription>
                </CardHeader>
                <CardContent>
                  <p className="text-3xl font-bold">{memStats.NumGoR}</p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>Heap System</CardTitle>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">
                    {formatBytes(memStats.HeapSys)}
                  </p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>Heap Idle</CardTitle>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">
                    {formatBytes(memStats.HeapIdle)}
                  </p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>Heap In Use</CardTitle>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">
                    {formatBytes(memStats.HeapInuse)}
                  </p>
                </CardContent>
              </Card>
              <Card
                className={`${stackCount ? "bg-red-100 text-red-800" : ""}`}
              >
                <CardHeader className="pb-2">
                  <CardTitle>Stack In Use</CardTitle>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">
                    {formatBytes(memStats.StackInuse)}
                  </p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>Stack System</CardTitle>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">
                    {formatBytes(memStats.StackSys)}
                  </p>
                </CardContent>
              </Card>
              <Card
                className={`${
                  gCCountBgColor ? "bg-green-100 text-green-800" : ""
                }`}
              >
                <CardHeader className="pb-2">
                  <CardTitle>GC Count</CardTitle>
                  <CardDescription>Number of collections</CardDescription>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">{memStats.NumGC}</p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>Total GC Pause</CardTitle>
                  <CardDescription>Cumulative pause time</CardDescription>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">
                    {formatNanoseconds(memStats.PauseTotalNs)}
                  </p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>Next GC Target</CardTitle>
                  <CardDescription>
                    Target heap size for next GC
                  </CardDescription>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">
                    {formatBytes(memStats.NextGC)}
                  </p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>GC System Memory</CardTitle>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">
                    {formatBytes(memStats.GCSys)}
                  </p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>Total Allocated</CardTitle>
                  <CardDescription>Cumulative allocation</CardDescription>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">
                    {formatBytes(memStats.TotalAlloc)}
                  </p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>Mallocs</CardTitle>
                  <CardDescription>Total allocations</CardDescription>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">{memStats.Mallocs}</p>
                </CardContent>
              </Card>
              <Card>
                <CardHeader className="pb-2">
                  <CardTitle>Frees</CardTitle>
                  <CardDescription>Total deallocations</CardDescription>
                </CardHeader>
                <CardContent>
                  <p className="text-2xl font-bold">{memStats.Frees}</p>
                </CardContent>
              </Card>
            </div>
          </TabsContent>
        </Tabs>
      )}
      <Dialog open={openModal} onClose={close}>
        <div className="fixed inset-0 flex items-center justify-center p-4">
          <DialogPanel
            transition
            className=" bg-card text-card-foreground flex flex-col gap-4 rounded-xl border shadow-sm p-6"
          >
            <DialogTitle className="text-lg font-bold">
              {stackCount
                ? "That's not a good idea"
                : "You have too many GoRoutines!"}
            </DialogTitle>
            <p>
              {stackCount
                ? "We're going to deallocate from stack so you don't accidentally blow up the server"
                : "You need to lower the number of GoRoutines you have before you continue"}
            </p>
            <div className="flex items-center justify-center space-x-4">
              {stackCount ? (
                <></>
              ) : (
                <>
                  <Button
                    onClick={noButtonClicked}
                    className="bg-red-100 text-red-800 gap-2"
                  >
                    Lower Basic Go Routines
                  </Button>
                  <Button
                    onClick={stackRemoveButtonClicked}
                    className="bg-red-100 text-red-800 gap-2"
                  >
                    Lower Stack Go Routines
                  </Button>
                  <Button
                    onClick={heapRemoveButtonClicked}
                    className="bg-red-100 text-red-800 gap-2"
                  >
                    Lower Heap Go Routines
                  </Button>
                </>
              )}
            </div>
          </DialogPanel>
        </div>
      </Dialog>
      <Dialog open={statusButtonWindow} onClose={closeStatusButtonClicked}>
        <div className="fixed inset-0 flex items-center justify-center p-4">
          <DialogPanel
            transition
            className=" bg-card text-card-foreground flex flex-col gap-4 rounded-xl border shadow-sm p-6"
          >
            <DialogTitle className="text-lg font-bold flex items-center justify-center ">
              Current Status
            </DialogTitle>
            <p
              className={`flex items-center justify-center ${
                backgroundColor ? " text-red-800" : "text-green-800"
              }`}
            >
              Go Routines Status: {backgroundColor ? "Bad" : "Good"}
            </p>
            <p
              className={`flex items-center justify-center ${
                allocBackgroundColor ? "text-red-800" : "text-green-800"
              }`}
            >
              Heap Allocation Status: {allocBackgroundColor ? "Bad" : "Good"}
            </p>
            <p
              className={`flex items-center justify-center ${
                stackCount ? "text-red-800" : "text-green-800"
              }`}
            >
              Stack Allocation Status: {stackCount ? "Bad" : "Good"}
            </p>
            <div className="flex items-center justify-center">
              <Button onClick={closeStatusButtonClicked}>Close</Button>
            </div>
          </DialogPanel>
        </div>
      </Dialog>
    </main>
  );
}
