# Inno22BUK
Bukh version of the Innoprojekt22 Code.

BUK1_H_ is the first iteration. It contains all the following:
- Plotter initialization, including all the motor and servo objects
- Initialization and calibration of coordinate system, include "test" csv (more below)
- Can read input from a CSV file (modified SVG code)
- Can draw straight line input curves and arcs

Perhaps to be added:
- Dynamic precision on high curvature curve segments

ERROR HANDLING
Error A1: The TIME_MAX maximum time for the execution of a motor command has been exceeded. The motors have been turned off.

Error C1: In the calibrate function, if no satisfactory integer is returned by the iscorrectmotor function (not -1, 0 or 1), this means that no button has been hit and the time has NOT been exceeded, which means the function has terminated for some other issue.

Error C2: Analog to C1 but for the iscorrectdirectionA function

Error C3: Analog to C2 but for the iscorrectdirectionB function

Error C4: This occurs when no satisfactory return is given for the calibratecorner function. This means that not all buttons were reached but the time limit has not elapsed, or any other default case was returned.

NEEDED
- Small code snippet to output servo angles when starting the build