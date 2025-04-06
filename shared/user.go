package shared

import "fmt"

type User struct {
	Name string `json:"name"`
}

func (user *User) Greetings() string {
	return fmt.Sprintf("[%v]: Aloha!", user.Name)
}
