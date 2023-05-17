<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="https://i.imgur.com/6wj0hh6.jpg" alt="Project logo"></a>
</p>

<h3 align="center">Tube Puzzle Game</h3>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
[![GitHub Issues](https://img.shields.io/github/issues/yourusername/tube-puzzle-game.svg)](https://github.com/suecarjayeswal/Tube_Puzzle/issues)
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/yourusername/tube-puzzle-game.svg)](https://github.com/suecarjayeswal/Tube_Puzzle/pulls)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---

<p align="center"> Tube Puzzle Game is a C++ game developed using Visual Studio and wxWidgets for GUI.
    <br>
</p>

## 📝 Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Built Using](#built_using)
- [File Structure](#file-structure)
- [Screenshots](#screenshots)
- [What We Learned](#what-we-learned)
- [Contributing](../CONTRIBUTING.md)
- [Authors](#authors)
- [Acknowledgments](#acknowledgement)

## 🧐 About <a name = "about"></a>

The Tube Puzzle Game is a C++ project that presents an engaging and challenging puzzle-solving experience. It involves arranging a grid of tubes in a specific order by swapping them within columns. The project utilizes the wxWidgets framework for the graphical user interface, allowing for an intuitive and visually appealing game interface.

To provide a dynamic gameplay experience, the levels in the Tube Puzzle Game are generated randomly with varying levels of difficulty. Each level presents a unique configuration of tubes that players must solve by strategically swapping and arranging them.

The project incorporates standard libraries and data structures, such as stack and linked list, to manage tube stacks and support undo/redo commands. These data structures facilitate efficient manipulation and storage of game actions. Additionally, algorithms are implemented for tube arrangement and game completion checks, ensuring a challenging and satisfying gameplay experience.

The Tube Puzzle Game's significance lies in its practical application of data structures and algorithms, providing a valuable learning tool for students studying Data Structures and Algorithms (DSA). It demonstrates how these concepts can be effectively utilized in real-world scenarios. The project serves as an interactive and educational resource, enabling DSA students to grasp the practical implementation of DSA concepts.

As for future aspects of the project, there is potential to enhance the game by implementing more complex levels and optimizing operations using advanced algorithms and data structures. This would further challenge players and improve the overall gameplay experience.

The Tube Puzzle Game offers a unique and entertaining way to develop problem-solving skills while exploring the applications of data structures and algorithms in a fun and interactive environment.


## 🏁 Getting Started <a name = "getting_started"></a>

To get a copy of the project up and running on your local machine, follow these steps:

### Prerequisites

- Visual Studio
- C++ compiler
- wxWidgets library

### Installation

1. Clone the repository to your local machine.
2. Open the project in Visual Studio.
3. Build the project to compile the source code.
4. Run the application and start playing the Tube Puzzle Game.

## 🎈 Usage <a name="usage"></a>

- Launch the game application.
- Follow the on-screen instructions to navigate through the game menu.
- Use the mouse or keyboard to interact with the game elements.
- Connect the tubes strategically to fill matching tube colors in columns.
- Solve the puzzles within the given constraints to win the game.

## ⛏️ Built Using <a name = "built-using"></a>

- C++ - Programming Language
- Visual Studio - Integrated Development Environment
- wxWidgets - GUI Library

## 📁 File Structure <a name = "file-structure"></a>

The project repository contains the following files and directories:
```
Tube_Puzzle/
├── readme.md
├── Tube_Puzzle/
│ ├── ActionStack.cpp
│ ├── ActionStack.h //contains code for stack that saves game Data
│ ├── App.cpp
│ ├── App.h     // the primary wxWidget init file
│ ├── GameControl.cpp
│ ├── GameControl.h     // contains Backend i.e. game logic
│ ├── MainFrame.cpp
│ ├── MainFrame.h       // the GUI layout of Game
│ ├── Queue.cpp
│ ├── Queue.h       // extra Queue Data structure for game for future
│ ├── stack.cpp
│ ├── stack.h       // stack for storing colors and ID in each column
│ ├── TubeSet.cpp
│ └── TubeSet.h     // class to deal with array of color of tubes in columns, with several functions to manipulate
│ ├── ClassDiagram.cd // the Class structure and relation diagram
└── Tube_Puzzle.sln
```
## 📷 Screenshots <a name="screenshots"></a>

Some screenshots of the Tube Puzzle Game:
---
<p align="center">

  <img src="https://github.com/suecarjayeswal/Tube_Puzzle/blob/IntialBranch/Screenshots/Screenshots/HomeScreen.png">
  <img src="https://github.com/suecarjayeswal/Tube_Puzzle//blob/IntialBranch/Screenshots/CompletionPage.png">
  <img src="https://github.com/suecarjayeswal/Tube_Puzzle//blob/IntialBranch/Screenshots/Others.png">
  <img src="https://github.com/suecarjayeswal/Tube_Puzzle//blob/IntialBranch/Screenshots/FlowOfExecution.png">
  <img src="https://github.com/suecarjayeswal/Tube_Puzzle//blob/IntialBranch/Screenshots/ClassesDesign.png">
</p>
---
## 💡 What We Learned <a name = "what-we-learned"></a>

While developing the Tube Puzzle Game project, we gained valuable experience in various areas, including:

- Utilizing data structures like **Stack and LinkedList** to manage game actions and tube connections.
- Implementing Object-Oriented Programming (**OOP**) principles to structure the game codebase.
- Dealing with **pointers** to efficiently manipulate and store game data.
- Leveraging **wxWidgets** library to create an interactive GUI for the game.

These experiences have enhanced our understanding of data structures, OOP concepts, and handling pointers in real-world applications.

## ✍️ Authors <a name = "authors"></a>

- [@suecarjayeswal](https://github.com/suecarjayeswal)
- Himanshu Gurung

See the list of [contributors](https://github.com/yourusername/tube-puzzle-game/contributors) who participated in this project.

## 🎉 Acknowledgements <a name = "acknowledgement"></a>

- Hat tip to anyone whose code or resources were used in this project.
- Inspiration: Bottle sort games in Playstore
## References

- [GUI learning Playlist wxWidgets C++](https://www.youtube.com/watch?v=BjQhp0eHmJw&list=PLFk1_lkqT8MbVOcwEppCPfjGOGhLvcf9G) (YouTube)
- [Event handling](https://www.youtube.com/watch?v=5v00F8hEV7E) (YouTube)


