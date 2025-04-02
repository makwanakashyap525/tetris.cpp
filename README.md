
## **Tetris Game in C++** 🎮  

A simple **Tetris game** implemented in C++ using `conio.h` for real-time input and `windows.h` for handling delays.  

### **Features** ✨  
✅ **Classic Tetris gameplay** with different tetromino shapes  
✅ **Real-time user input handling** using arrow keys  
✅ **Line clearing and scoring system**  
✅ **Hard Drop** feature for instant block placement  
✅ **Automatic movement and game-over detection**  

### **Installation & Compilation** 🔧  
1. Clone the repository:  
   ```bash
   git clone https://github.com/your-username/tetris-cpp.git
   cd tetris-cpp
   ```
2. Compile the code using a C++ compiler (like `g++`):  
   ```bash
   g++ tetris.cpp -o tetris.exe
   ```
3. Run the game:  
   ```bash
   ./tetris.exe
   ```  

> **Note:** This game is designed for **Windows** as it uses `<conio.h>` and `<windows.h>`. For Linux/Mac, modifications may be needed.

### **How to Play** 🎮  
| Key  | Action          |
|------|----------------|
| ←    | Move left      |
| →    | Move right     |
| ↓    | Move down faster |
| ↑    | Rotate piece   |
| Space | Hard drop (Instant placement) |

### **Gameplay Mechanics**  
- Blocks fall **automatically** over time  
- If a **row is completely filled**, it gets cleared and **score increases**  
- If a new piece **cannot spawn**, the game **ends**  

### **Contributing** 🤝  
Want to improve the game?  
1. **Fork** the repository  
2. Create a **new branch** (`git checkout -b feature-branch`)  
3. **Commit changes** (`git commit -m "Added a new feature"`)  
4. **Push to GitHub** (`git push origin feature-branch`)  
5. Submit a **Pull Request** 🚀  



