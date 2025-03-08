package main

import (
	"fmt"
	cf "gofiles/custom-functions"
	"math/rand"
	"net"
	"slices"
	"strings"
	"sync"
	im "gofiles/importing/imports.go" // random imports to see if adding packages adds to build time 
	imo "gofiles/importing/imports1.go"
	imt "gofiles/importing/imports2.go"
) 

var log = cf.InitLogger()
var m sync.Mutex
var numClients int = 0

func start() {
	
	l, err := net.Listen("tcp", ":1000")
	if err != nil {
		log.Println(err)
		return
	}

	defer l.Close()
	for {
		con, err := l.Accept()
		if err != nil {
			log.Println(err)
			return
		}

		if numClients == 2 {
			log.Println("Max clients!")
			continue
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
	words := []string{"loon", "mourningdove", "shimaenaga", "awebo", "chicken"}
	index := rand.Intn(len(words))

	word := words[index]
	numGuesses := 0

	for len(guessedIndexes) != len(word) && numGuesses < 5 {
		bufferMessage := "Your word is!: \n"
		for i:= 0; i < len(word); i++ {
			if slices.Contains(guessedIndexes, i) {
				bufferMessage += fmt.Sprintf(" %c ", word[i])
			} else {
				bufferMessage += " _ "
			}
		}
		bufferMessage += "\nGuess a character in the word!"

		// First write that is sent 
		_, err := conn.Write([]byte(bufferMessage))
		
		if err != nil {
			log.Println(err)
			return
		}

		recv := make([]byte, 1024)
		n, err := conn.Read(recv)
		if err != nil {
			log.Println(err)
			return
		}

		guess := strings.TrimSpace(string(recv[:n]))
		fmt.Printf("What %s", guess)
		check := 0

		prevGuessCount := len(guessedIndexes)
		tempWord := []rune(word)
		for check != -1 {
			fmt.Println("Entered!")
			check = strings.Index(string(tempWord), guess)
			fmt.Println(check)
			if check != -1 {
				guessedIndexes = append(guessedIndexes, check)
				tempWord[check] = '_'
			}
		}

		result := ""
		if len(guessedIndexes) > prevGuessCount {
			result = "You guessed a correct letter!"
		} else {
			result = "Oof"
		}
		// Second write that is sent 
		_, err = conn.Write([]byte(result))
		if err != nil {
			log.Println(err)
			return
		}
		numGuesses++
	}
	
	finished := ""
	if numGuesses == 5 && len(guessedIndexes) != len(word) {
		finished = "Maybe next time!"
	} else {
		finished = fmt.Sprintf("You won! The word was %s", word)
	}

	// Third write that is sent 
	_, err := conn.Write([]byte(finished))
	if err != nil {
		log.Println(err)
		return
	}
}


func main() {
	start()
}