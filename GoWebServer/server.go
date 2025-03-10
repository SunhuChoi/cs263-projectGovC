package main

import (
	"fmt"
	"log"
	"net/http"
	"runtime"
	"time"

	"github.com/gorilla/websocket"
)


type MemStats struct {
	Alloc	uint64 `json:"Alloc"`      
	TotalAlloc	uint64 `json:"TotalAlloc"` 
	Sys	uint64 `json:"Sys"`        
	Mallocs	uint64 `json:"Mallocs"`   
	Frees	uint64 `json:"Frees"`      
	LiveObjects	uint64 `json:"LiveObjects"` 

	HeapAlloc	uint64 `json:"HeapAlloc"` 
	HeapSys	uint64 `json:"HeapSys"`    
	HeapIdle	uint64 `json:"HeapIdle"`   
	HeapInuse	uint64 `json:"HeapInuse"`  
	HeapReleased	uint64 `json:"HeapReleased"` 
	HeapObjects	uint64 `json:"HeapObjects"` 

	// Stack statistics
	StackInuse	uint64 `json:"StackInuse"`  
	StackSys	uint64 `json:"StackSys"`    

	// Garbage collector statistics
	NextGC	uint64 `json:"NextGC"`       
	LastGC	uint64 `json:"LastGC"`       
	PauseTotalNs	uint64 `json:"PauseTotalNs"` 
	NumGC	uint32 `json:"NumGC"`        
	GCSys	uint64 `json:"GCSys"`        
	NumGoR	uint32 `json:"NumGoR`
}

var upgrader = websocket.Upgrader{
	ReadBufferSize:  1024,
	WriteBufferSize: 1024,

	CheckOrigin: func(r *http.Request) bool {
		return r.Header.Get("origin") == "http://localhost:3000"
	},
}

var clients = make(map[*websocket.Conn]bool)
var gochans = make([]chan bool, 0)
var stackchans = make([]chan bool, 0)
var heapchans = make([]chan bool, 0)

func getMemStats() MemStats {
	var ms runtime.MemStats
	runtime.ReadMemStats(&ms)

	stats := MemStats{
		Alloc:	ms.Alloc,
		TotalAlloc:	ms.TotalAlloc,
		Sys:	ms.Sys,
		Mallocs:	ms.Mallocs,
		Frees:	ms.Frees,
		LiveObjects:	ms.Mallocs - ms.Frees,
		HeapSys:	ms.HeapSys,
		HeapIdle:	ms.HeapIdle,
		HeapInuse:	ms.HeapInuse,
		HeapReleased:	ms.HeapReleased,
		HeapObjects:	ms.HeapObjects,
		StackInuse:	ms.StackInuse,
		StackSys:	ms.StackSys,
		GCSys:	ms.GCSys,
		NextGC:	ms.NextGC,
		PauseTotalNs:	ms.PauseTotalNs,
		NumGC:	ms.NumGC,
		NumGoR:	uint32(runtime.NumGoroutine())-3,
	}

	allocMem()
	return stats
}

func allocMem() {
	garbage := make([]byte, 1024*1024)
	for i := 0; i < len(garbage); i++ {
		garbage[0] = byte(1)
	}
}


func handleWebSocket(w http.ResponseWriter, r *http.Request) {
	fmt.Println("This is probably a go routine ngl")
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Printf("Error upgrading to WebSocket: %v", err)
		return
	}
	defer conn.Close()

	clients[conn] = true
	defer delete(clients, conn)
	log.Printf("New WebSocket client connected from %s", conn.RemoteAddr())

	stats := getMemStats()
	err = conn.WriteJSON(stats)
	if err != nil {
		log.Printf("Error sending initial stats: %v", err)
		return
	}

	flag := make(chan bool)
	go broadcastMemStats(conn, flag)

	for {
		_, m, err := conn.ReadMessage()
		if err != nil {
			log.Printf("Error reading message: %v", err)
			break
		}
		fmt.Println(string(m))
		if string(m) == "Add" {
			fmt.Println("Added a goroutine")
			conn.WriteMessage(websocket.TextMessage, []byte("Nice!"))

			flag := make(chan bool)
			gochans = append(gochans, flag)
			go randGoRoutine(flag)
		} else if string(m) == "Remove" {
			if len(gochans) != 0 {
				gochans[len(gochans)-1]<-true
				gochans = gochans[:len(gochans)-1]
				fmt.Println("Removed a goroutine")
			} else {
				fmt.Println("No more goroutines!")
			}
			conn.WriteMessage(websocket.TextMessage, []byte("Nice!"))
		} else if string(m) == "Stack" {
			fmt.Println("Allocating the stack")
			conn.WriteMessage(websocket.TextMessage, []byte("Nice!"))

			flag := make(chan bool)
			stackchans = append(stackchans, flag)
			go stackAllocator(1, flag)
		} else if string(m) == "Stack Remove" {
			if len(stackchans) != 0 {
				stackchans[len(stackchans)-1]<-true
				stackchans = stackchans[:len(stackchans)-1]
				fmt.Println("Removed stack calls")
			} else {
				fmt.Println("No more stack calls!")
			}
		} else if string(m) == "Heap" {
			fmt.Println("Allocating to the heap")
			conn.WriteMessage(websocket.TextMessage, []byte("Nice!"))

			flag := make(chan bool)
			heapchans = append(stackchans, flag)
			go heapAllocator(flag)
		} else if string(m) == "Heap Remove" {
			if len(heapchans) != 0 {
				heapchans[len(heapchans)-1]<-true
				heapchans = heapchans[:len(heapchans)-1]
				fmt.Println("Removed heap calls")
			} else {
				fmt.Println("No more heap calls!")
			}
		} 
	}
	
	flag <- true
}

func heapAllocator(flag chan bool) {
	garbage := make([]byte, 1024*1024)
	for {
		select {
		case <- flag:
			return
		default:
			garbage[0] = byte(1)
		}
	}
}

func stackAllocator(i int, flag chan bool) {
	select {
	case <- flag:
		return
	default:
		time.Sleep(5*time.Microsecond)
		stackAllocator(i, flag)
	}
}

func randGoRoutine(flag chan bool) {
	for {
		select {
		case <- flag:
			return
		}
	}
}

func broadcastMemStats(conn *websocket.Conn, flag chan bool) {
	for {		
		select {
		case <- flag:
			return
		default:
			time.Sleep(1*time.Second)
			stats := getMemStats()
			conn.WriteJSON(stats)
		}
	}
}


func main() {
	http.HandleFunc("/ws", handleWebSocket)
	port := 8080
	fmt.Printf("Server starting on port %d...\n", port)
	fmt.Printf("WebSocket endpoint: ws://localhost:%d/ws\n", port)
	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%d", port), nil))
}

