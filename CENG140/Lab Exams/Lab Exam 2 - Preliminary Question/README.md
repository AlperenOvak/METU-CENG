# Task 1 - Length of a Vector  (20 Pts)


You are given

            A vector vec=(v1,v2,v3⋯vn)

You will find the length of the vector which is simply:

|vec|=v21+v22+⋯+v2n−−−−−−−−−−−−−−√

For this task, you will implement the function that is given blank in lab_2.c file:

            float length(float vec[], int size);
                vec: an array of floats, example [5.0, 4.0, 1.0]
                size: size of the array. For example the array above has size 3

It will be guaranteed that:

            0<s≤100

            components of the vector are floating points

Your function should just return the resulting float value which is the length. 

While calculating the square root, you have to use sqrt function which is defined in the c math library.

We have already included <math.h> header file in lab_2.c for you so you can directly use sqrt.

Important Note: Remember, unlike the last lab exam (where you got inputs from stdin using scanf),

all the inputs have already been provided to you by passing as function arguments. Just implementing the

function and returning the resulting value is enough.

Sample Input Outputs:

Args1 :  

size = 1

vec = [1.1]

Return1 :

1.10

Args2 :  

size = 2

vec = [8.0, 15.0]

Return2 :

17.00

Args3 :  

size = 5

vec = [1.4, 4.3, 2.112, 6.19, 10.5]

Return3 :

13.17

# Task 2 - Dot product  (20 Pts)


You are given

            A vector A=(a1,a2,a3⋯an)

A vector B=(b1,b2,b3⋯bn)

You will find the dot product of these vectors A⋅B

. 

The dot product of two vectors is found by:

A⋅B=∑i=0nai∗bi=a1∗b1+a2∗b2+a3∗b3+⋯+an∗bn

For this task, you will implement the function that is given blank in lab_2.c file:

                float dot(float vec1[], float vec2[], int size);
                    vec1: an array of floats, example [3.0, 4.0, 5.0]
                    vec2: an array of floats, example [1.5, 2.0, 2.5]
                    size: size of vec1 and vec2 arrays. For example the arrays above have size 3

It will be guaranteed that:

            Sizes of both vectors are equal (m=n

) and 0<n≤100

            The components of both vectors will be floats

Your function should just return the resulting float value which is the dot product. The Important Note

section in Task1 applies here as well.

Sample Input Outputs:

Args1 :  

size = 1

vec1 = [1.5]

vec2 = [2.5]

Return1 :

3.75

Args2 :  

size = 2

vec1 = [3.0, 4.0]

vec2 = [3.0, 4.0]

Return2 :

25.00

Args3 :  

size = 6

vec1 = [2.3, 4.77, 1.20, 1.65, 1.01, 2.2]

vec2 = [1.2, 0.64, 9.12, 0.34, 3.15, 2.1]

Return3 :

25.12

# Task 3 - Translate Vertices  (30 Pts)

You are given

            An array of 2-D vertices vertices=(v1x,v1y,v2x,v2y⋯vnx,vny)

. This represents an object's vertices on a 2-D plane

    For example, if the vertices array is [1.0, 1.0, 2.0, 2.0], this means that the vertices of the object are:
        v1 = (1.0,1.0)
        v2 = (2.0,2.0)

An array of commands commands=(C1x,C1y,C2x,C2y,⋯,Cnx,Cny)

                For example, if there are two translation commands as [1.0, 1.1, 1.2, 1.3]
                    We have two commands, c1 = [1.0, 1.1] and c2 = [1.2, 1.3]. We apply both of these commands to all vertices of the object.
                    Lets assume we have vertices array [1.0, 1.0, 2.0, 2.0] as above and this means there are two vertices v1 =[1.0, 1.0] and v2 = [2.0,2.0]. After applying these two commands, our new vertices become:
                        After first command [1.0, 1.1]
                            v1_new = (1.0 + 1.0, 1.0 + 1.1)
                            v2_new = (2.0 + 1.0, 2.0 + 1.1)
                        After second command [1.2, 1.3]
                            v1_new = (2.0 + 1.2, 2.1 + 1.3)
                            v2_new = (3.0 + 1.2, 3.1 + 1.3)

After applying the translations to all vertices, you will PRINT new vertices with two-digit precision "%.2f":

In this task, you will be implementing the function:

            void translateVertices(float vertices[], int vertexCount, float commands[], int commandCount);
                This is a function with void type, so it does not return a value, you will use printf and output to stdout
                vertices: An array of x,y coordinates for every vertex as it is explained above
                vertexCount: number of vertices, Note that array vertices 's size becomes vertexCount * 2
                commands: An array of translation commands. Details have been explained above
                commandCount: number of commands. Note that array command's size becomes commandCount * 2

It will be guaranteed that:

    The components of vertices and commands arrays will be floats

Your function should PRINT the resulting new vertex array as specified below. You will not return anything in this function. 


    Sample Input Outputs:

Args1 :  

vertexCount = 1

vertices = [1.0, 1.0]

commandCount = 2

commands = [-0.5, 0.5, 2.0, 2.0]

Output1 :

2.50 3.50

Args2 :  

vertexCount = 2

vertices = [1.54, 2.21, 0.65, 0.90]

commandCount = 3

commands = [1.0, -1.0, 0.0, 1.0, -1.0, 0.0]

Output2 :

1.54 2.21 0.65 0.90

Args3 :  

vertexCount = 4

vertices = [1.0, 1.5, 3.6, 3.0, 0.85, 0.60, 1.4, 1.9]

commandCount = 4

commands = [0.5, -0.5, 0.75, 0.75, -1.5, 1.5, 0.25, 0.25]

Output3 :

1.00 3.50 3.60 5.00 0.85 2.60 1.40 3.90

# Task 4 - Visualize Objects (30 Pts)
In this task, you are given:

            Row size of a 2D Grid
            Column size of a 2D Grid
            Object A's vertices in 2D (a1x,a1y,a2x,a2y,⋯,anx,any)

Object B's vertices in 2D (b1x,b1y,b2x,b2y,⋯,bmx,bmy)

By using the vertices of these two objects, you will display them in a 2D Grid.

In this task, you will implement the function:

    void visualizeObjects(int A[], int vertexCountA, int B[], int vertexCountB, int rowSize, int columnSize);
        A: Object A's vertices
        vertexCountA: A's vertex count. Note that array A's size becomes vertexCountA * 2
        B: Object B's vertices
        vertexCountB: B's vertex count. Note that array B's size becomes vertexCountB * 2
        rowSize: height of the grid
        columnSize: column of the grid


Specifications:

            The upper-left corner of the grid has (0,0) coordinate, lower-right corner's coordinate is (rowSize-1, columnSize-1)
            Vertex counts of A and B will be as 1≤n,m≤10

            Vertex coordinates are integers
            It is guaranteed that rowSize and columnSize values are integer values that are greater than or equal to 3
            To display object A's vertices -> put the character 'a' to that coordinate
            To display object B's vertices -> put the character 'b' to that coordinate
            If two vertices overlap -> put the character 'x' to that coordinate
            If there are no objects at that coordinate put the character '-'
            Vertex coordinates are always in the bounds of the 2D grid
            Vertices of an object may not be connected. For example (0.0,0.0) and (1.0, 5.0)
            There will be two spaces "  " between elements in the same row
                Spaces are only between inner elements of the row (There is no space before the first element of a row or after the last element of a row)

Your function should PRINT the resulting grid as specified below. You will not return anything in this function. 

    Sample Input Outputs

Args1:

rowSize = 4

columnSize = 5

vertexCountA = 4

vertexCountB = 2

A = [0, 0, 0, 1, 1, 0, 1, 1]

B = [2, 3, 3, 3]

Output 1:

aa---

aa---

---b-

---b-

Input 2:

rowSize = 3

columnSize = 3

vertexCountA = 2

vertexCountB = 2

A = [1, 0, 1, 1]

B = [1, 1, 1, 2]

Output 2:

---

axb

---

Input 3:

rowSize= 4

columnSize = 9

vertexCountA = 5

vertexCountB = 4

A = [2, 2, 2, 3, 2, 4, 2, 5, 2, 6]

B = [0, 4, 1, 4, 2, 4, 3, 4]

Output 3:

-  -  -  -  b  -  -  -  -

-  -  -  -  b  -  -  -  -

-  -  a  a  x  a  a  -  -

-  -  -  -  b  -  -  -  -
