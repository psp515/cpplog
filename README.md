<div align="center">

  <h1> cpplog </h1>
  <p>  C+ + = C++ = C# ? </p>

  <div>
    <a href="">
      <img src="https://img.shields.io/github/last-commit/psp515/cpplog" alt="last update" />
    </a>
    <a href="https://github.com/psp515/cpplog/network/members">
      <img src="https://img.shields.io/github/forks/psp515/cpplog" alt="forks" />
    </a>
    <a href="https://github.com/psp515/cpplog/stargazers">
      <img src="https://img.shields.io/github/stars/psp515/cpplog" alt="stars" />
    </a>
    <a href="https://github.com/psp515/cpplog/issues/">
      <img src="https://img.shields.io/github/issues/psp515/cpplog" alt="open issues" />
    </a>
    <a href="https://github.com/psp515/cpplog/blob/master/LICENSE">
      <img src="https://img.shields.io/github/license/psp515/cpplog" alt="license" />
    </a>
  </div>
</div>  

<br/>

## About

This repository provides a lightweight and extensible logger implementation in C++, 
designed with simplicity and flexibility in mind. 
Built using C++20 and tested with the MinGW compiler, 
this project is ideal for developers who want full control over logging without relying on external libraries.

✨ Key Features
- 📦 No external dependencies – relies solely on the C++ Standard Library.
- 🔌 Extensible design – easily add custom `Sink` to direct logs wherever you need.
- ⚙ Minimal and clear – straightforward codebase focused on transparency and maintainability.

This logger serves as a solid foundation for custom logging solutions tailored to your specific needs.

> Solution was implemented as a project during studies at Politechnika Warszawska.

## Built With

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white&style=flat)
![CLion](https://img.shields.io/badge/CLion-000000?style=for-the-badge&logo=clion&logoColor=white&style=flat)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white&style=flat)

## Configuration examples

### Global Logger

The logger instance is managed internally by the library, so users can simply access 
and use it whenever needed—no manual lifetime management.

```
int main() {
    // Custom file sink options
    const FileSinkOptions options;

    // Configure global logger
    LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addStdoutSink()
        .addFileSink(options)
        .configure();

    // Log data
    CppLog::info("Hello World!");
    CppLog::debug(source_location::current(),"Debug message {0}", 345);
}
```

> You configure global logger using `configure()` method.

### Local Logger

This logger is designed for custom lifetime management—users are responsible for creating the logger 
instance and managing its lifetime via a pointer.

```
int main() {
    // Custom file sink options
    const FileSinkOptions options;

    // Configure global logger
    auto logger = LoggerConfiguration()
        .setLoggerFilteringLevel(INFO)
        .addStdoutSink()
        .addFileSink(options)
        .build();

    // Log Data
    logger.info("Hello World!");
    logger.debug(source_location::current(),"Debug message {0}", 346);
}
```

> You can get local logger using `build()` method.

## Details

This logger is built with flexibility and extensibility in mind, 
offering a wide range of configuration options and support for custom log destinations (sinks).
Below is a breakdown of the key features provided by the library.

📌 Base Features
- ✅ Multiple log levels supported
- 🎚 Per-sink log level filtering, each sink can define its own minimum log level to control what gets logged.
- 📝 Flexible output formats, supports both **plain text** and **JSON log** formatting.
- 🧵 Rich context support, optionally include thread ID, function name, and source code line number in log entries.

📌 Multi-sink Support

Supports configuring and using multiple sinks simultaneously, 
allowing logs to be routed to different outputs at the same time.

📌 Custom Sinks

Easy to extend with custom sinks, simply by implementing the sink interface.

📌 Built-in Sink Types

- ConsoleSink – logs to standard output (stdout).
- FileSink – logs to a file.
- RotatingFileSink – logs to a file with automatic rotation, new file is created after a defined size limit is reached. You can specify the maximum number of historical log files to keep.
- (Example implementation for MinGW) HttpSink – sends logs via HTTP/1.1, acts as an HTTP client sending log entries to a configured server endpoint. (repository also contains example http server under `server` folder)

### Testing
The library includes a comprehensive test suite built using Google Test. 
These tests ensure the core functionality of the logger works as expected. 
They verify, for instance, that log entries are correctly written to a file, 
that the logger properly filters messages based on their severity level, 
and that different sinks behave as intended. 
The tests also serve as a reference for how to integrate and configure the logger in a typical application setup.

### Run example

A complete usage example is included in the repository to demonstrate how the logger can be integrated into a project (`example` folder). 
The example shows how to initialize the logger with a basic sink, 
such as logging to the console, 
and how to configure additional sinks like file logging or HTTP endpoints. 
It illustrates how multiple sinks can be used at the same time, 
each with their own log level or format settings. 
The example also highlights the logger’s thread-safety by showing how it handles concurrent logging from multiple threads, 
making it suitable for multi-threaded applications.

Easies way to run example is to use clion:
- open clion
- add configuration CMake application `example`
- for this configuration set workdir to `build` folder (default `cmake-build-debug`)
- run example

### Internal Structure

Internal structure is shown on below class diagram.

![Architecture](/docs/Cpplog.drawio.png)

### License

Distributed under the MIT License. See `LICENSE` for more information.

### Contact

<div>
  <a href="https://www.linkedin.com/in/lukasz-psp515-psp515r/">
    <img src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white" alt="LinkedIn" />
  </a>
  <a href="https://twitter.com/psp515">
    <img src="https://img.shields.io/badge/Twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white" alt="Twitter" />
  </a>
</div>


