# import sys


tankcapacity_X = 9
tankcapacity_Y = 4
empty = 0
goal = 6
Maxlength = 100
# hang chuoi de in cac hanh dong
action = ["First State", "pour Water Full X", "pour Water Full Y", "pour Water Empty X",
       "pour Water Empty Y", "pour Water X to Y", "pour Water Y to X"]


class State:
   def __init__(self, x, y):
       self.x = x
       self.y = y


def makeNullState(state):
   state.x = 0
   state.y = 0


def print_State(state: State):
   print("  X: {}  --- Y: {}".format(state.x, state.y))


def goalcheck(state):
   return state.x == 6 or state.y == 6


def pourWaterFullX(cur_state, result):
   if cur_state.x < tankcapacity_X:
       result.x = tankcapacity_X
       result.y = cur_state.y
       return 1
   return 0


def pourWaterFullY(cur_state, result):
   if cur_state.y < tankcapacity_Y:
       result.y = tankcapacity_Y
       result.x = cur_state.x
       return 1
   return 0


def pourWaterEmptyX(cur_state, result):
   if cur_state.x > 0:
       result.x = empty
       result.y = cur_state.y
       return 1
   return 0


def pourWaterEmptyY(cur_state, result):
   if cur_state.y > 0:
       result.y = empty
       result.x = cur_state.x
       return 1
   return 0


def pourWaterXY(cuz_state, result):
   if cuz_state.x > 0 and cuz_state.y < tankcapacity_Y:
       result.x = max(cuz_state.x - (tankcapacity_Y - cuz_state.y), empty)
       result.y = min(cuz_state.x + cuz_state.y, tankcapacity_Y)
       return 1
   return 0
def pourWaterYX(cuz_state, result):
   if cuz_state.y > 0 and cuz_state.x < tankcapacity_X:
       result.y = max(cuz_state.y - (tankcapacity_X - cuz_state.x), empty)
       result.x = min(cuz_state.y + cuz_state.x, tankcapacity_X)
       return 1
   return 0


def call_operator(cuz_state, result, option):
   switcher = {
       1: pourWaterFullX,
       2: pourWaterFullY,
       3: pourWaterEmptyX,
       4: pourWaterEmptyY,
       5: pourWaterXY,
       6: pourWaterYX
   }
   func = switcher.get(option, lambda: "Loi!")
   return func(cuz_state, result)


class Node:
   def __init__(self):
       self.state = None
       self.Parent = None
       self.no_function = 0


class Stack:
   def __init__(self):
       # self.Elements = [None] * Maxlength
       # self.Top_idx = Maxlength
       self.Elements = []
       self.Top_idx = 0
def push(x, stack):
   if stack.Top_idx == 0:
       print("Loi! Ngan xep da day.")
   else:
       stack.Top_idx -= 1
       stack.Elements[stack.Top_idx] = x


def makeNull_Stack(stack):
   stack.Top_idx = Maxlength


def empty_Stack(stack):
   return stack.Top_idx == Maxlength


def full_Stack(stack):
   return stack.Top_idx == 0


def top(stack):
   if not empty_Stack(stack):
       return stack.Elements[stack.Top_idx]
   return None


def pop(stack):
   if not empty_Stack(stack):
       stack.Top_idx += 1
   else:
       print("Loi! Ngan xep dang rong.")


class Queue:
   def __init__(self):
       self.Elements = [None] * Maxlength
       self.front = -1
       self.rear = -1


def makeNull_Queue(queue):
   queue.front = -1
   queue.rear = -1


def empty_Queue(queue):
   return queue.front == -1


def full_Queue(queue):
   return ((queue.rear - queue.front + 1) % Maxlength) == 0


def get_Front(queue):
   if empty_Queue(queue):
       print("Queue rong!")
   return queue.Elements[queue.front]


def compareStates(A, B):
   return A.x == B.x and A.y == B.y


def find_State(state, Q: Queue):
   tempQueue = Q.copy()
   while len(tempQueue) != 0:
       if compareStates(tempQueue[0].state, state):
           return 1
       tempQueue.pop(0)
   return 0


def BFS_Algorithm(state):
   Open_BFS = []
   Close_BFS = []
   root = Node()
   root.state = state
   root.Parent = None
   root.no_function = 0
   Open_BFS.append(root)
   while Open_BFS:
       node = Open_BFS[0]
       Open_BFS.pop(0)
       Close_BFS.append(node)
       if goalcheck(node.state):
           return node
       for opt in range(1, 7):
           newstate = State(0,0)
           makeNullState(newstate)
           if call_operator(node.state, newstate, opt):
               if find_State(newstate, Close_BFS) or find_State(newstate, Open_BFS):
                   continue
               newNode = Node()
               newNode.state = newstate
               newNode.Parent = node
               newNode.no_function = opt
               Open_BFS.append(newNode)
   return None


def print_WaysToGetGoal(node):
   stackPrint = []
   while node.Parent != None:
       stackPrint.append(node)
       node = node.Parent
   stackPrint.append(node)
   no_action = 0
   while stackPrint:
       print("\nAction {}: {}".format(no_action, action[stackPrint[-1].no_function]))
       print_State(stackPrint[- 1].state)
       stackPrint.pop()
       no_action += 1
def main():
   cuz_state = State(0, 0)
   p = BFS_Algorithm(cuz_state)
   print_WaysToGetGoal(p)


if __name__ == "__main__":
   main()
