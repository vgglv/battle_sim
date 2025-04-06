package main

import (
	"fmt"
	"net"
	"os"

	"github.com/vgglv/battle-sim/shared"
)

func main() {
	// Connect to the TCP server
	conn, err := net.Dial("tcp", "127.0.0.1:8080")
	if err != nil {
		fmt.Println("Error connecting to server:", err)
		os.Exit(1)
	}
	defer conn.Close()

	user := shared.User{Name: "Master"}

	for {
		message := user.Greetings()
		_, err := conn.Write([]byte(message))
		if err != nil {
			fmt.Println("Error sending message:", err)
			return
		}

		buffer := make([]byte, 1024)
		n, err := conn.Read(buffer)
		if err != nil {
			fmt.Println("Error reading response:", err)
			return
		}

		fmt.Printf("Server response: %s\n", string(buffer[:n]))
	}
}
