### **MasterMind**
***
![Logo](banner/MasterMind.png.png)
***
MasterMind, a minimized shell, interpreting logical operators **&&** with **||** and **Parenthesis** only for prioritization, parsing input, and executing commands, with integrated builtins such as ***echo***, ***export***, ***cd***, ***pwd***, ***env...*** along with expanding enverionment variables.
***

**Valgo's side in the project:**

* **Grammar identification**, identifiying **Pipes**, **And**s, **Or**s, **Input/Output/Append Redirection** and **Parenthesis**.
* **Syntax Verification**, consicutive **Pipes**, **And**s, **Or**s, multiple **Parenthesis** not splited by operators, **Redirections** misuse. 
* **Re-Identification** of the previous identification template, by specifiying **Commands** from **arguments**.
* **Shunting Yard Algorithm**, intended to create a new expression out of the input, handling priority for **Pipes**, **And**s, **Or**s and **Parenthesis**.
* **Tree Creation**, Tree created based on the algorithm expression, in which each node has an element from the input.

**OussMac's side in the project:**