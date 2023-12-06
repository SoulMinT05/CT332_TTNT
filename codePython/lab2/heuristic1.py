row = 3
col = 3
empty = 0


class Coord:
    def __init__(self, x, y):
        self.row = x
        self.col = y

    def show(self):
        # print("(x,y) = (%d,%d)" % (self.row, self.col))
        print("(x,y) = ({},{})".format(self.row, self.col))


class State:
    def __init__(self, input = None):
        if input == None:
            input = []
            for i in range(row):
                input.append(list(range(i * col, i * col + col)))
        self.data = input
        for i in range(col):
            for j in range(row):
                if self.data[i][j] == 0:
                    self.empty = Coord(i, j)

    def copyState(self): #copy ra 1 cái State y chang
        input = []
        for i in range(row):
            rowData = []
            for j in range(col):
                rowData.append(self.data[i][j])
            input.append(rowData)
        return State(input)


    def show(self, script="SHOW STATE"):
        # print("------%s----" % script)
        print("-------{}----".format(script));
        for i in range(row):
            for j in range(col):
                # print("{}".format(self.data[i][j]))
                print(self.data[i][j], end=' ')
            print()

    def moveUp(self):
        eRow = self.empty.row
        eCol = self.empty.col
        if eRow > 0:
            self.empty.row -= 1
            self.data[eRow][eCol] = self.data[eRow - 1][eCol]
            self.data[eRow - 1][eCol] = empty
            return 1
        return 0

    def moveDown(self):
        eRow = self.empty.row
        eCol = self.empty.col
        if eRow < row - 1:
            self.empty.row += 1
            self.data[eRow][eCol] = self.data[eRow + 1][eCol]
            self.data[eRow + 1][eCol] = empty
            return 1
        return 0

    def moveLeft(self):
        eRow = self.empty.row
        eCol = self.empty.col
        if eCol > 0:
            self.empty.col -= 1
            self.data[eRow][eCol] = self.data[eRow][eCol - 1]
            self.data[eRow][eCol - 1] = empty
            return 1
        return 0

    def moveRight(self):
        eRow = self.empty.row
        eCol = self.empty.col
        if eCol < col - 1:
            self.empty.col += 1
            self.data[eRow][eCol] = self.data[eRow][eCol + 1]
            self.data[eRow][eCol + 1] = empty
            return 1
        return 0

    def callOperator(self, option):
        if option == 0:
            return self.moveUp()
        elif option == 1:
            return self.moveDown()
        elif option == 2:
            return self.moveLeft()
        elif option == 3:
            return self.moveRight()
        else:
            print("Option not Valid")
            return 0

    def compareStates(state1, state2):
        if state1.empty.col != state2.empty.col or state1.empty.row != state2.empty.row:
            return 0
        for i in range(row):
            for j in range(col):
                if state1.data[i][j] != state2.data[i][j]:
                    return 0
        return 1

    def heuristic1(state, goal):
        count = 0
        for i in range(row):
            for j in range(col):
                if goal.data[i][j] != state.data[i][j]:
                    count += 1
        return count

    def heuristic2(state, goal):
        count = 0
        for i in range(row):
            for j in range(col):
                if state.data[i][j] != goal.data[i][j] and goal.data[i][j] != 0:
                    for row_g in range(row):
                        for col_g in range(col):
                            if state.data[i][j] == goal.data[row_g][col_g]:
                                count += abs(i - row_g) + abs(j - col_g)
                                col_g = j
                                row_g = i
                                break
        return count


def sortList(list):
    for i in range(len(list)):
        for j in range(i+1, len(list)):
            if list[i].heuristic > list[j].heuristic:
                node = list[i]
                list[i] = list[j]
                list[j] = node


def findItem(item, list):
    for i in list:
        if item.compareStates(i.state):
            return item   #item = element_at(i, list) ben C
    return None


class Node:
    def __init__(self, state=State(), option=0, parent=None):
        self.state = state.copyState()
        self.option = option
        self.parent = parent
        self.heuristic = self.state.heuristic2(goal)
    def show(self):
        # self.state.show("Node Show")
        print("Heuristic : {}".format(self.heuristic))
        # print("Option : ",self.option)

    def solveEigthPuzle(self):
        Open = [self]
        Close = []
        # Open.append(self)
        while Open is not None:
            # print("LEN OF OPEN LIST :",len(Open))
            node = Open.pop(0)
            Close.append(node)
            # X.state.show("Check State POP")
            # print("\n\n")
            if (node.state.compareStates(goal)): #goalcheck
                return node
            for option in range(maxOperator):
                newState = node.state.copyState()
                # newState.heuristic = self.state.heuristic1(goal)

                if newState.callOperator(option):
                    if findItem(newState, Open) == None and findItem(newState, Close) == None:
                        newNode = Node(newState, option, node)
                        Open.append(newNode)
                        sortList(Open)

            # if k==5 : break
        return None



    def print_WaysToGetGoal(self):
        list = []
        X = self
        while X != None:
            list.append(X)
            # X.state.show()
            # print(X.option)
            X = X.parent

        i = 0
        while len(list) != 0:
            Y = list.pop()
            Y.state.show("Action %d : %s" % (i, action[Y.option]) if i != 0 else "Action 0 : First State")
            i += 1


action = ["MoveUp", "MoveDown", "MoveRight", "MoveLeft"]
maxOperator = 4

#Main Function
goal = State([[0, 1, 2], [3, 4, 5], [6, 7, 8]])
# goal = State([[1, 2, 3], [8, 0, 4], [7,6,5]])
# goal = State()
# goal.show("Goal State")
print("\n")
input = [[3, 4, 5], [1, 0, 2], [6, 7, 8]]
# input = [[2,8,3], [1,6,4], [7,0,5]]
S = State(input)
# S.show("Start State")

root = Node(S)
result = root.solveEigthPuzle()
result.print_WaysToGetGoal()

