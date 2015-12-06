Small(?) project to learn how to C.

Run `export CC=/path/to/clang` or set `-std=gnu99` in `Makefile` otherwise this will fail to compile.

Build with `make`.

Criteria:

* [Y] You'll probably need standard library functions like those in string.h (http://pubs.opengroup.org/onlinepubs/7908799/xsh/string.h.html). Implement them as you need them. Don't do it all at once.
* [Y] Figure out how to use scanf to read user input and print it back with printf.
* [Y] Figure out how to use malloc and free and secure the user input from overflows using the %ms format specifier with scanf.
* [Y] Implement an "offline" simple HTTP server: the user will type a simple HTTP GET request (e.g. "GET /something HTTP/1.0\r\n") and you'll print back some arbitrary data depending on the request uri.
* [Y] Figure out how to read and write files and list directory contents. Write dumbed down versions of ls and cat. You may use standard library functions for this. (Hint: you'll need to figure out how argc and *argv[] work.)
* [] Figure out how to send and receive data to/from TCP sockets. Just write a simple server you can talk to with telnet. After you send a message to it with telnet, print that message to the console (you may use printf) and send back a message through the socket informing the client that you correctly received it. There was a really good document about socket programming but I can't find it. In the meanwhile this (http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html) should suffice.
* [] Apply what you did for your "offline HTTP server" to sockets. Communicate with the user through sockets with telnet instead of using the terminal.
* [] Instead of returning arbitrary responses, now return files in the current directory that match the requested uri.
* [] Implement full HTTP/1.1 (GET) requests and responses as opposed to the simple HTTP/1.0 ones you've been using until now. http://www.w3.org/Protocols/rfc2616/rfc2616.html chapters 4 through 6. Implement checks for badly formatted requests and return proper responses. In short, implement what you need for the status codes 200, 400 and 404. If it didn't so far, now everything should work with a web browser too.
* [] Only after everything works well and you're feeling pretty confident, try to make a multithreaded (with pthreads) socket server like that of point 6. To test it, simply open multiple telnet connections to it. If it only responds to one, it isn't working. If data from one thread is infecting another thread, kill yourself.
* [] Apply the knowledge now acquired to make the HTTP server multithreading and respond to multiple requests at the same time.
* [] Eat cookie.
