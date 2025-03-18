# Learning Go and Benchmarking Against C

## Team Members
- Raina Kakani
- Sunhu Choi

## Vision Statement 
For this project, we want to understand the differences in performance between C and Golang. While both are statically-typed languages, their design decisions are drastically different. We want to learn to implement common algorithms in Golang and understand the challenges of learning this newer language. We also want to know the rationale behind choosing Golang over an older, heavily tested language like C or vice-versa.
We’re aiming to compare Golang and C by evaluating key performance factors like memory usage, execution speed, and compilation time. One major part of this comparison will be analyzing how Go’s garbage collection impacts performance, especially in contrast to C, which uses manual memory management. We’ll also look at how the languages handle polymorphism and how Golang’s type safety affects runtime efficiency compared to C’s more flexible (but less safe) approach. To really test the strengths and weaknesses, we will run some heavy-duty algorithms like matrix multiplication and deep recursion. Additionally, we’ll create various mini-projects—such as those involving computationally heavy tasks, algorithms that use different data structures, and memory-intensive operations—to better understand how each language handles these challenges and compare their performance across different use cases.
https://docs.google.com/document/d/1F_ny6PRYJya3hDUXRv73d4O9bccZJnMd89J7JwcBGDo/edit?usp=sharing

## Project Notes: 
- https://docs.google.com/document/d/1Hq9C0rBVcCdx30qyi7RJSmlMp9FwIhzgGhFGFXvW0-8/edit?usp=sharing

## Installation Steps 
This project requires you have Go downloaded and ready to use. If you don't please check out this page: https://go.dev/doc/install. Make sure the download option you choose corresponds to your device type.

### Running the Go Web Server
To run the Go Web Server, you need to have Node.js installed. If you do not have Node.js, or if your current version is outdated, please check out this page: https://nodejs.org/en/download. Make sure you donwload the correct version for your device type. Once you have downloaded Node.js, run the command "node -v" in your CLI to make sure it has been downloaded. 

Once downloaded, open up two terminals. In both, CD into the GoWebServer directory. In one of them, cd into the go-frontend subdirectory under GoWebServer. You will have to download all the node modules the app is dependent on. To do this, run the command "npm i". Once all the node modules have been installed, run the command "npm run dev". You should eventually see this in your terminal:
![image](https://github.com/user-attachments/assets/821d65b0-8ea0-46ca-9322-1b6d6e6b3ad3)

In the other terminal, run the command "go run server.go". This should find the server.go file under the GoWebServer directory. If you are on windows, you will most likely be prompted with something like this:
![image](https://github.com/user-attachments/assets/7b5fd56d-ce61-4395-97f7-2424f7360fc7)

Click Allow. Your server should now be running and listening in on Port 8080 for a Websocket connection. 

