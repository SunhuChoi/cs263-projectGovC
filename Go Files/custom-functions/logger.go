package customfunctions

import (
	"fmt"
	"log"
	"os"
	"time"
) 


func InitLogger() *log.Logger {
    if _, err := os.Stat("log"); os.IsNotExist(err) {
        os.Mkdir("log", 0750)
    }

    logFile, err := os.OpenFile(fmt.Sprintf("log/%s-sunhu", time.Now().Format("2006-01-02-15-04-05")), os.O_CREATE|os.O_RDWR|os.O_APPEND, 0644)
    if err != nil {
        log.Fatal(err)
    }

    // Set up the logger
    var logger *log.Logger = log.New(logFile, "INFO: ", log.Ldate|log.Ltime|log.Lshortfile)
    return logger
}