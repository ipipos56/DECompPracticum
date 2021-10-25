#Application Description
This application is made for calculating numerical methods and exact solution of IVP with
Ordinary Differential Equation (ODE) of the first order. In my work I used a Model-View-
Controller design pattern because it is an advantageous pattern for applications with one
Graphical User Interface (GUI). “Model” is used for calculating numerical methods and
exact solution. “View” is used for GUI redrawing. “Controller” is used for communication
between “Model” and “View” parts (for getting values from GUI, start recalculating of
graphs and setting data for plotting). Application is made in QT Creator v5.12.11 with C++
language. You can see the source code in the DE folder

#Model part
The biggest class “Model” has 9 child classes in which 3 is abstract. The main inner class
is “Updater” which is responsible for starting recalculations of methods, solutions and
approximation errors. Also, “Model” has an abstract “Function” which is used in
calculating exact solution (ExactSolution abstract class). Both these classes have extended
classes for implementing “MyFunction” and “MyExactSolution”. The last part of the
“Model” is “NumericalMethod” abstract class which is extended by 3 numerical methods
of calculating IVP with ODE of the first degree.

#View part
The “View” class is used for drawing GUI and sending information from GUI to the
“Controller” class.

#Controller part
The “Controller” class is used for getting data from “View” class, starting computations in
the “Model” class and after that sending computational results back for redrawing graphs.

#Utils part
The “Utils” class have 3 base structures for convenient data use in the application.
Structure “Point” is used for basic point representation for graphs, structure “GUIValues”
for sending GUI information between “View” and “Controller” class, structure
“ModelValues” for storing base information for calculating exact solution and numerical
methods.
