maxCol = 9
maxRow = 9
blockCol = 3
blockRow = 3
runTime = 0
maxValue = 10
empty = 0




class Coord:
   def __init__(self, x=0, y=0):
       self.x = x
       self.y = y


   def show(self):
       print("Toa Do (x,y) = (%d,%d)" % (self.x, self.y))


   def indexOf(self):
       return self.x * maxRow + self.y




def positionOfVertex(vertex):
   coord = Coord()
   coord.x = int(vertex / maxRow)
   coord.y = vertex % maxCol
   return coord




class Constrain:
   def __init__(self):
       self.data = [[0] * 81]
       for i in range(80):
           self.data.append([0] * 81)
       self.n = maxRow * maxCol


   def addConstrain(self, source, target):
       source = Coord()
       target = Coord()
       u = source.indexOf()
       v = target.indexOf()
       # print("Add Constrain : %d %d  = %d" %(u,v,self.data[u][v]) )
       if (self.data[u][v] == 0):
           # print("Add Constrain : %d %d " %(u,v))
           self.data[u][v] = 1
           self.data[v][u] = 1
           return 1
       return 0


   def speardConstrain(self, coord, changed):
       # coord = Coord()
       # constrain = Constrain()
       # changed = []
       row = coord.x
       col = coord.y
       # print("Speard Coord :")
       # coord.show()
       # print("---")
       for i in range(maxRow):  # Theo Columns
           if i != row:
               pos = Coord(i, col)
               # newCoord.show()
               if (self.addConstrain(coord, pos)):
                   changed.append(pos)


       for i in range(maxCol):  # Theo Row
           if i != col:
               pos = Coord(row, i)
               # newCoord.show()
               if (self.addConstrain(coord, pos)):
                   changed.append(pos)


       for i in range(blockCol):  # Theo Block
           for j in range(blockRow):
               areaX = int(row / blockRow) * blockCol
               areaY = int(col / blockCol) * blockRow
               if areaX + i != row or areaY + j != col:
                   pos = Coord(areaX + i, areaY + j)
                   # newCoord.show()
                   if (self.addConstrain(coord, pos)):
                       changed.append(pos)


   def getConstrain(self, coord):  #viết vậy thế cho ListCoord luôn
       # constrain = Constrain()
       # coord = Coord()
       # print("Run getConstrain of : ")
       # coord.show()
       # print("---------------------")
       v = coord.indexOf()
       result = []
       for i in range(self.n):
           if (self.data[v][i] == 1):
               # positionOfVertex(i).show()
               result.append(positionOfVertex(i))
       return result




class Sudoku:
   def __init__(self, input=None): #typedef struct Sudoku (ko hiểu lắm)
       self.cell = [[0] * maxRow] * maxCol if input == None else input
       self.constrain = Constrain()


   def initSudoku(self):
       for i in range(maxRow):
           for j in range(maxCol):
               self.cell[i][j] = empty
       #không khởi tạo initConstrains luôn


   def initSudokuWithValue(self, input):
       self.cell = input #này không tạo vòng lặp i, j mà gán bằng input luôn


   def show(self):
       print("Sudoku State :")
       print("-------------------------------")
       for row in range(maxRow):
           # if(row%blockRow ==0):
           #     print("               \n")  #không cần vì xấu
           for col in range(maxCol):
               if col % blockCol == 0:
                   print("|", end='')
               print(" %d " % (self.cell[row][col]), end='')
               # if col == maxCol - 1: print("|", end='')
           print("")
           if row % blockRow == blockRow - 1: #có cái này cho đỡ xấu, khi được 1 ô 9 số rồi sẽ có ----
               print("-------------------------------")


   def isFilled(self):
       for i in range(maxCol):
           for j in range(maxRow):
               if self.cell[i][j] == empty:
                   return 0
       return 1


   def getAvailableValue(self, position):  # self is Sudoku
       posList = self.constrain.getConstrain(position)


       availables = [0] * maxValue
       for i in range(1, maxValue):
           availables[i] = 1
       for i in range(len(posList)):
           pos = Coord(posList[i].x, posList[i].y)  # bằng Coord pos = posList.data[i]
           if (self.cell[pos.x][pos.y] != empty):
               # pos.show()
               # print(self.cell[pos.x][pos.y])
               availables[self.cell[pos.x][pos.y]] = 0
       result = []


       for i in range(1, maxValue):
           if availables[i] != 0:
               result.append(i)
       # print(result,availables)
       return result


   def getNextEmpty(self):
       for i in range(maxRow):
           for j in range(maxCol):
               pos = Coord(i, j)
               if self.cell[i][j] == empty:
                   return pos


   def getNextMin(self):
       minLength = maxValue
       for i in range(maxRow):
           for j in range(maxCol):
               if self.cell[i][j] == empty:
                   pos = Coord(i, j)
                   availableLength = len(self.getAvailableValue(pos))
                   if availableLength < minLength:
                       minLength = availableLength
                       result = pos
       return result


   def sudokuBackTracking(self):
       if self.isFilled():
           return 1
       # position = self.getNextEmpty()
       position = self.getNextMin()
       global runTime
       runTime = runTime + 1
       # position.show()
       available = self.getAvailableValue(position)
       # print("Available : ",available,len(available))
       if len(available) == 0:
           return 0


       for j in range(len(available)):
           value = available[j]
           self.cell[position.x][position.y] = value


           if (self.sudokuBackTracking()): return 1


           self.cell[position.x][position.y] = empty


       return 0


   def solveSudoku(self):
       # print("\n\nStart SOLVE SUDOKU : ")
       self.constrain = Constrain()
       for i in range(maxRow):
           for j in range(maxCol):
               # if self.cell[]
               if (self.cell[i][j] != empty):
                   history = []
                   pos = Coord(i, j)
                   # pos.show()
                   self.constrain.speardConstrain(pos, history)
       if self.sudokuBackTracking() == 1:
           print("Solved\n")
       else:
           print("Cannot Solve")
       print("Run Times : %d" % (runTime))




###Main Function


input = [
   [5, 3, 0, 0, 7, 0, 0, 0, 0],
   [6, 0, 0, 1, 9, 5, 0, 0, 0],
   [0, 9, 8, 0, 0, 0, 0, 6, 0],
   [8, 0, 0, 0, 6, 0, 0, 0, 3],
   [4, 0, 0, 8, 0, 3, 0, 0, 1],
   [7, 0, 0, 0, 2, 0, 0, 0, 6],
   [0, 6, 0, 0, 0, 0, 2, 8, 0],
   [0, 0, 0, 4, 1, 9, 0, 0, 5],
   [0, 0, 0, 0, 8, 0, 0, 7, 9]]


start = Sudoku(input)
start.show()
start.solveSudoku()
start.show()
