package main

import (
	"fmt"
	"log"
	"net"
)

func main() {
	address := "127.0.0.1:8080"

	listener, err := net.Listen("tcp", address)
	if err != nil {
		log.Fatal(err)
	}
	defer listener.Close()
	fmt.Println("TCP server listening on", address)
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("Error accepting connection:", err)
			continue
		}
		fmt.Println("Client connected:", conn.RemoteAddr())
		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
	defer conn.Close()
	buffer := make([]byte, 1024)
	for {
		n, err := conn.Read(buffer)
		if err != nil {
			fmt.Println("Error reading from connection:", err)
			return
		}
		fmt.Println("Received:", string(buffer[:n]))
		//_, err = conn.Write(buffer[:n])
		//if err != nil {
		//	fmt.Println("Error writing to connection:", err)
		//	// this closes connection right?
		//	return
		//}
	}
}
