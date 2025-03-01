package main

import (
	cf "gofiles/custom-functions"
	"math/rand"
	"net"
	"strings"
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
	guessedIndexes := make([]int, 0)
	words := []string{"chicken", "awebo", "mourning dove", "loon"}
	index := rand.Intn(len(words))

	word := words[index]
	numGuesses := 0

	for len(guessedIndexes) != len(words) || numGuesses < 5 {
		log.Println("Your word is!: ")
		for i:= 0; i < len(word); i++ {
			log.Print(" _ ")
		}
		log.Println()
		log.Println("Guess a character in the word!")

		recv := make([]byte, 1024)
		_, err := conn.Read(recv)
		if err != nil {
			log.Println(err)
			return
		}

		guess := string(recv)
		check := 0

		prevGuessCount := len(guessedIndexes)
		for check != -1 {
			check = strings.Index(guess, word[check:])
			if check != -1 {
				guessedIndexes = append(guessedIndexes, check)
			}
		}

		if len(guessedIndexes) > prevGuessCount {
			log.Println("You guessed a correct letter!")
		} else {
			log.Println("oof")
		}
	}
}


func main() {
	start()
}