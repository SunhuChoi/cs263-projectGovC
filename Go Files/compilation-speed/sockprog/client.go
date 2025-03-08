package main

import (
	"fmt"
	cf "gofiles/custom-functions"
	"net"
	"strings"
)

var log = cf.InitLogger()

func main() {
	con, err := net.Dial("tcp", "localhost:1000")
	if err != nil {
		log.Println(err)
		return
	}

	log.Println("Connected!")

	defer con.Close()
	totGuesses := 0

	for totGuesses < 5 {
		recv := make([]byte, 1024)
		n, err := con.Read(recv)
		if err != nil {
			log.Println(err)
			return
		}
	
		result := strings.TrimSpace(string(recv[:n]))
		log.Println(result)
		if strings.Contains(result, "You won!") {
			break
		}

		var guess string
		fmt.Scanln(&guess)
		_, err = con.Write([]byte(guess))
		if err != nil {
			log.Println(err)
			return
		}

		recv = make([]byte, 1024)
		_, err = con.Read(recv)
		if err != nil {
			log.Println(err)
			return
		}
		log.Println(strings.TrimSpace(string(recv[:n])))
		totGuesses++
	}

	recv := make([]byte, 1024)
	n, err := con.Read(recv)
	if err != nil {
		log.Println(err)
		return
	}

	result := strings.TrimSpace(string(recv[:n]))
	log.Println(result)

}