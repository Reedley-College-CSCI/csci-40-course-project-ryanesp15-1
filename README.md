[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7mdzU3H2)
# CS1 Final Project - [Pitch Tracker]

## 1. Overview
- What problem does your project solve?
- Answer: My projected helped maybe parents or sibilings of pitchers in the sport of baseball track their pitchers statistics. Something simple for younger players to get an idea of how statistics will be in the future of their athletic careers.
- Briefly describe the purpose and key features of your program.
- Answer: My program is able to store pitch data on 4 types of pitches. It can also export the data on the pitches as well as display it to the user for them to see. 

---

## 2. Design Decisions
- What fundamental programming constructs and data types did you use, and why?
- Answer: My main was the struct Pitch that held pitch data(type, speed, result, location). I also used the banned vector called pitchLog its simple for when you are adding and removing pitches. There are a total of 9 functions as well plus the main function. Most of the work was done in the void functions and it made the coding a lot more easier and cleaner. I also used validation looks like the while loops in my addNewPitch function, it made it sure there were valid inputs from the user.
- Why did you choose to structure your data using structs?
- Answer: Grouping the variables (speed, location, type, and result) under the pitch struct makes the code easier to read. Its better that using 4 separate arrays. 
- How did you implement searching and sorting? What algorithms did you use and why?
- Answer: I implemented the linear search in the calculateStats function. I used a simple for loop to go through the entire pitchLog vector, I was looking for a specific pitch type, and any other occurances of it. I used a bubble sort in the sortPitchesBySpeed function. I needed to sort the pitches by speed in descending order and the bubble sort did that for me, so thats why I chose it.
- How do you ensure data persistence between program runs?
- Answer: I heavily rely on 2 functions, the pitchesToFile and pitchesFromFile functions. The pitchesToFile function is called at the end of the program when the user exits selecting option5. I use an ofstream to send out the contents of the pitchLog to pitch_log.txt. The loadPitchesFromFile fuunction is called immedieately using an ifstream to import any data in the text file that was already there. the "while(inFile.." loop is what ensures the previous data is imported into the vector.
- Did you consider alternative approaches? If so, why did you not use them?  
Answer: Yes I was thinking of using a binary search, but obviously it requires the data to be sorted. It would also just find me the first postion of the first matching item I needed.
---

## 3. Testing Summary
- **Structured Testing Log:** Include a table with test cases, expected output, actual output, and pass/fail status.  
- What testing methods did you use?
- Answer: Below are the test cases I used to test functionality. I placed these test cases in an Excel for better readability for my sake, and then I inputted the results into the columns. Below are my test results.
-  TC-01 | Normal/Valid Input (Log a valid pitch) | 1 (Add Pitches) -> FB -> HA -> S -> 95 -> X (Quit Input) | [SUCCESS] Pitch logged: FB at 95mph. ACTUAL OUTPUT: [SUCCESS] Pitch logged: FB at 95mph./Returning to main menu…
-  TC-02 | Invalid Input (Type & Speed) (Test input validation) | 1 (Add Pitches) -> XX (Invalid Type) -> FB (Valid) -> HM -> S -> abc (Invalid Speed) -> 55 (Valid Speed) -> X | Invalid pitch type (XX)...   [!] Invalid speed entered. Pitch discarded...   [SUCCESS] Pitch logged: FB at 55mph. ACTUAL OUTPUT: After inputing "XX", progam would bug out and loop. Needed to input a cin.ignore to get passed. Changed some output designs and was able to successfully see expected output.
-  TC-03 | Searching Algorithm Test (Calculate stats for a valid pitch type) | 3 (Calculate Stats) -> FB -> X | STATISTICS FOR PITCH TYPE: FB   Total Thrown: 2 (From TC-01 & TC-02)   Strikes (S): 2 (100.0%). ACTUAL OUTPUT:Inputted 3 FB pitch data inputs. All requested outputs displayed correctly.
-  TC-04 | Data Persistence Test (Save and Load data) | 5 (Save and Exit) -> (Re-run program) | [INFO] Successfully saved 2 pitches...   (On restart) [INFO] Successfully loaded 2 pitches...ACTUAL OUTPUT:Saved 2 pitches to pitch log successfully. On restart output of loading pitches was successful.
-  TC-05 | Sorting Algorithm Test (Export data sorted by speed) | 4 (Export Data to TXT) | [INFO] Pitch log sorted by speed...   [SUCCESS] Exported 2 pitches... (Must check pitch_data_report.txt contents).ACTUAL OUTPUT:Exported 2 pitches and they displayed fastest to slowest successfully. Pitches were saved to "pitch_data_report.txt".
-  TC-06 | Invalid Location (Edge case for invalid code) | 1 (Add Pitches) -> FB -> MMMM (Invalid Location) -> MM (Valid) -> B -> 88 -> X | Invalid location (MMMM)...   [SUCCESS] Pitch logged: FB at 88mph. ACTUAL OUTPUT: Invalid location displayed but was grouped with the output statement requesting the new pitch type. Cleaned up the output and expected outputs displayed successfully.

- Provide examples of test inputs (valid and invalid) and describe how your program responds.  

---

## 4. Technical Walkthrough
- Explain the main functionality of your program.  
- **Include a link to your required video demonstration** showcasing how the project works (**3-7 minutes**).
- Answer: https://youtu.be/L6PfH2hQGRU
    Make sure it shareable without approval needed.

---

## 5. Challenges and Lessons Learned
- What challenges did you encounter while working on this project?
- Answer: Lots of logical errors. the addNewPitchFunction along with its do-while loops had my brain hurting, and me running into a lot of problems with the program had me reseaching more into better ways to code. 
- What key lessons did you learn about programming and problem-solving?
- Answer: I learned that you should be testing every, single, step, of, the, way. Even if you believe you dont need to test, do it. Ensuring fucntionality in even a small block of code is worth all the while because it may come back and bite you. I also learned a lot about the structure of the code. Seeing how simple my main fucntion is and how complicated the seperate functions are, it made me believe that I can create similar functions that cover seperate issues. The structure became a lot more clearer once i cleaned up the code and made it nice.

---

## 6. Future Improvements
- If you had more time, what changes or enhancements would you make?
- Answer: For the future, I would really work on the output design and a little bit more functionality. For the output design, I would probably research more into cool designs or GUI's i would say that can be displayed through the console output. Thinking about it right now I could have probably Googled how to make it better, oh well. For functionality, I would want to add some additional features, maybe exporting to a .csv, or even including more pitch types for higher level pitchers. I can honestly see this program growing a lot and I feel its super simplistic with the console output, I wonder if it would still be simple if I added more functions.

