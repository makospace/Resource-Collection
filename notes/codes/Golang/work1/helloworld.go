//写一个输出helloworld的程序
package main

import (
    "fmt"
    // "math/rand"
    // "strings"
    "time"
)

type Point struct {
    x, y int
}

func gopherSleep(i int) {
    time.Sleep(time.Second)
    fmt.Println("Gopher", i, "is sleeping")
}

// func main() {  //go的大括号的左括号必须和函数在同一行，右括号单独占一行
//     // fmt.Println("Hello, world", "My name is", "Go")  //有逗号会自动加空格
//     // //Go不支持++，--前缀
//     // var num = rand.Intn(10)  //rand是一个包，Intn是一个函数，返回一个随机数
//     // fmt.Println(num)
//     // var commend = "outside"
//     // var result = strings.Contains(commend, "o") //Go存在短路逻辑
//     // fmt.Println(result)
//     // //Go的switch采用了fallthrough显式的穿透
//     // // var counter = 10 //=> counter := 10
//     // // for counter >= 0 {
//     // //     fmt.Println(counter)
//     // //     counter --
//     // //     time.Sleep(time.Second)
//     // // }
//     // // for counter = 10; counter >= 0; counter-- {
//     // //     fmt.Println(counter)
//     // //     time.Sleep(time.Second)
//     // // }
//     // switch num1 := rand.Intn(10); num1 {
//     //     case 0:
//     //         fmt.Println("-1")
//     //     case 1:
//     //         fmt.Println("-2")
//     //     case 2:
//     //         fmt.Println(num1)
//     // }
//     // //浮点数默认是float64
//     // var num2 float32 = 1.2  //显式声明float32
//     // fmt.Printf("%05.2f", num2)
//     // p := Point{x : 1, y : 2}
//     // fmt.Println(p)
//     type Scheme string

//     const (
//         HTTP  Scheme = "http"
//         HTTPS Scheme = "https"
//     )

//     fmt.Println(HTTP, HTTPS)

//     for i := 0; i < 10; i ++ {
//         go gopherSleep(i)
//     }
//     time.Sleep(time.Second * 15)
// }
