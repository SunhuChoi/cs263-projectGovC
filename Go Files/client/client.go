package main

import (
	cf "gofiles/custom-functions"
	"net"
)

var log = cf.InitLogger()

func main() {
	con, err := net.Dial("tcp", "localhost:1000")
	if err != nil {
		log.Println(err)
		return
	}

	log.Println("Connected!")
	con.Close()
}