package main

import (
	cf "gofiles/custom-functions"
	"math/rand"
	"net"
	"sync"
) 

var log = cf.InitLogger()
var m sync.Mutex

func start() {
	
	l, err := net.Listen("tcp", ":1000")
	if err != nil {
		log.Println(err)
		return
	}

	defer l.Close()
	numClients := 0
	for {
		if numClients == 2 {
			log.Println("Max clients!")
			continue
		}
		con, err := l.Accept()
		if err != nil {
			log.Println(err)
			return
		}

		go handler(con)

		m.Lock()
		numClients++
		m.Unlock()
	}

}

func handler(conn net.Conn) {
	defer conn.Close()
	words := []string{"chicken", "awebo", "mourning dove", "loon"}
	index := rand.Intn(len(words))

	log.Println("Your word is!: ")
	for i:= 0; i < index; i++ {
		log.Print(" _ ")
	}
	log.Println()
	log.Println("Guess the word!")

}


func main() {
	start()
}