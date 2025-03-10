"use client";

import { useEffect, useRef } from "react";

interface MemStats {
  Alloc: number;
  TotalAlloc: number;
  Sys: number;
  Mallocs: number;
  Frees: number;
  LiveObjects: number;
  PauseTotalNs: number;
  NumGC: number;
  HeapAlloc: number;
  HeapSys: number;
  HeapIdle: number;
  HeapInuse: number;
  StackInuse: number;
  StackSys: number;
  GCSys: number;
  NextGC: number;
  LastGC: number;
}

interface MemoryChartProps {
  memStats: MemStats;
}

export default function MemoryChart({ memStats }: MemoryChartProps) {
  const canvasRef = useRef<HTMLCanvasElement>(null);

  useEffect(() => {
    if (!canvasRef.current || !memStats) return;

    const canvas = canvasRef.current;
    const ctx = canvas.getContext("2d");
    if (!ctx) return;

    // Clear canvas
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Set up dimensions
    const width = canvas.width;
    const height = canvas.height;
    const padding = 40;
    const chartWidth = width - padding * 2;
    const chartHeight = height - padding * 2;

    // Draw background
    ctx.fillStyle = "#f9fafb";
    ctx.fillRect(0, 0, width, height);

    // Memory categories to display
    const memoryData = [
      { name: "Heap In Use", value: memStats.HeapInuse, color: "#3b82f6" },
      { name: "Heap Idle", value: memStats.HeapIdle, color: "#93c5fd" },
      { name: "Stack", value: memStats.StackSys, color: "#10b981" },
      { name: "GC Sys", value: memStats.GCSys, color: "#f59e0b" },
    ];

    // Calculate total for percentage
    const totalSys = memStats.Sys;

    // Draw bar chart
    const barWidth = chartWidth / memoryData.length - 20;

    // Draw title
    ctx.fillStyle = "#111827";
    ctx.font = "bold 16px sans-serif";
    ctx.textAlign = "center";
    ctx.fillText("Memory Usage Breakdown", width / 2, padding / 2);

    // Draw bars
    memoryData.forEach((item, index) => {
      const percentage = item.value / totalSys;
      const barHeight = chartHeight * percentage;
      const x = padding + index * (barWidth + 20);
      const y = height - padding - barHeight;

      // Draw bar
      ctx.fillStyle = item.color;
      ctx.fillRect(x, y, barWidth, barHeight);

      // Draw value on top of bar
      ctx.fillStyle = "#111827";
      ctx.font = "12px sans-serif";
      ctx.textAlign = "center";
      const valueText = formatBytes(item.value);
      ctx.fillText(valueText, x + barWidth / 2, y - 5);

      // Draw percentage inside bar if there's enough space
      if (barHeight > 20) {
        ctx.fillStyle = "#ffffff";
        ctx.fillText(
          `${(percentage * 100).toFixed(1)}%`,
          x + barWidth / 2,
          y + barHeight / 2
        );
      }

      // Draw label below bar
      ctx.fillStyle = "#111827";
      ctx.fillText(item.name, x + barWidth / 2, height - padding + 15);
    });

    // Draw total system memory
    ctx.fillStyle = "#111827";
    ctx.font = "14px sans-serif";
    ctx.textAlign = "right";
    ctx.fillText(
      `Total System Memory: ${formatBytes(totalSys)}`,
      width - padding,
      padding / 2
    );
  }, [memStats]);

  const formatBytes = (bytes: number) => {
    if (bytes === 0) return "0 Bytes";
    const k = 1024;
    const sizes = ["Bytes", "KB", "MB", "GB"];
    const i = Math.floor(Math.log(bytes) / Math.log(k));
    return (
      Number.parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + " " + sizes[i]
    );
  };

  return (
    <div className="w-full">
      <canvas
        ref={canvasRef}
        width={800}
        height={300}
        className="w-full h-auto"
      />
    </div>
  );
}
