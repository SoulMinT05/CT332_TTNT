# import sys
tankcapacity_X = 10
tankcapacity_Y = 5
tankcapacity_Z = 6
empty = 0
goal = 8
Maxlength = 100
# hang chuoi de in cac hanh dong
action = ["First State", "pour Water X to Y", "pour Water X to Z", "pour Water Y to X", "pour Water Y to Z", "pour Water Z to X", "pour Water Z to Y"]


class State:
   def __init__(self, x, y, z):
       self.x = x
       self.y = y
       self.z = z


def makeNullState(state):
   state.x = 0
   state.y = 0
   state.z = 0


def print_State(state: State):
   print("  X: {}  --- Y: {} --- Z: {}".format(state.x, state.y, state.z))


def goalcheck(state):
   return state.x == goal or state.y == goal or state.z == goal


def pourWaterFullX(cur_state, result):
   if cur_state.x < tankcapacity_X:
       result.x = tankcapacity_X
       result.y = cur_state.y
       result.z = cur_state.z
       return 1
   return 0


def pourWaterFullY(cur_state, result):
   if cur_state.y < tankcapacity_Y:
       result.y = tankcapacity_Y
       result.x = cur_state.x
       result.y = cur_state.y
       return 1
   return 0


def pourWaterFullZ(cur_state, result):
   if cur_state.z < tankcapacity_Z:
       result.z = tankcapacity_Z
       result.x = cur_state.x
       result.y = cur_state.y
       return 1
   return 0


def pourWaterEmptyX(cur_state, result):
   if cur_state.x > 0:
       result.x = empty
       result.y = cur_state.y
       result.z = cur_state.z
       return 1
   return 0


def pourWaterEmptyY(cur_state, result):
   if cur_state.y > 0:
       result.y = empty
       result.x = cur_state.x
       result.z = cur_state.z
       return 1
   return 0


def pourWaterEmptyZ(cur_state, result):
   if cur_state.z > 0:
       result.z = empty
       result.x = cur_state.x
       result.y = cur_state.y
       return 1
   return 0


def pourWaterXY(cuz_state, result):
   if cuz_state.x > 0 and cuz_state.y < tankcapacity_Y:
       result.x = max(cuz_state.x - (tankcapacity_Y - cuz_state.y), empty)
       result.y = min(cuz_state.x + cuz_state.y, tankcapacity_Y)
       result.z = cuz_state.z
       return 1
   return 0


def pourWaterXZ(cuz_state, result):
   if cuz_state.x > 0 and cuz_state.z < tankcapacity_Z:
       result.x = max(cuz_state.x - (tankcapacity_Z - cuz_state.z), empty)
       result.z = min(cuz_state.x + cuz_state.z, tankcapacity_Z)
       result.y = cuz_state.y
       return 1
   return 0


def pourWaterYX(cuz_state, result):
   if cuz_state.y > 0 and cuz_state.x < tankcapacity_X:
       result.y = max(cuz_state.y - (tankcapacity_X - cuz_state.x), empty)
       result.x = min(cuz_state.y + cuz_state.x, tankcapacity_X)
       result.z = cuz_state.z
       return 1
   return 0


def pourWaterYZ(cuz_state, result):
   if(cuz_state.y > 0 and cuz_state.z < tankcapacity_Z):
       result.y = max(cuz_state.y - (tankcapacity_Z - cuz_state.z), empty)
       result.z = min(cuz_state.y + cuz_state.z, tankcapacity_Z)
       result.x = cuz_state.x
       return 1;
   return 0;


def pourWaterZX(cuz_state, result):
   if(cuz_state.z > 0 and cuz_state.x < tankcapacity_X):
       result.z = max(cuz_state.z - (tankcapacity_X - cuz_state.x), empty)
       result.x = min(cuz_state.z + cuz_state.x, tankcapacity_X)
       result.y = cuz_state.y
       return 1
   return 0


def pourWaterZY(cuz_state, result):
   if(cuz_state.z > 0 and cuz_state.y < tankcapacity_Y):
       result.z = max(cuz_state.z - (tankcapacity_Y - cuz_state.y), empty)
       result.y = min(cuz_state.z + cuz_state.y, tankcapacity_Y)
       result.x = cuz_state.x
       return 1
   return 0;


def call_operator(cuz_state, result, option):
   switcher = {
       1: pourWaterXY,
       2: pourWaterXZ,
       3: pourWaterYX,
       4: pourWaterYZ,
       5: pourWaterZX,
       6: pourWaterZY
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


def compareStates(A, B):
   return A.x == B.x and A.y == B.y and A.z == B.z


def find_State(state: State, L: list):
   tempList =  L.copy()
   while (len(tempList) != 0):
       if compareStates(tempList[-1].state, state):
           return 1
       tempList.pop()
   return 0


def DFS_Algorithm(state):
  Open_DFS = []
  Close_DFS = []
  root = Node()
  root.state = state
  root.Parent = None
  root.no_function = 0
  Open_DFS.append(root)
  while Open_DFS:
      node = Open_DFS[-1]
      Open_DFS.pop()
      Close_DFS.append(node)
      if goalcheck(node.state):
          return node
      for opt in range(1, 7):
          newstate = State(0, 0, 0)
          makeNullState(newstate)
          if call_operator(node.state, newstate, opt):
              if find_State(newstate, Close_DFS) or find_State(newstate, Open_DFS):
                  continue
              newNode = Node()
              newNode.state = newstate
              newNode.Parent = node
              newNode.no_function = opt
              Open_DFS.append(newNode)
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
   cuz_state = State(10, 0, 0)
   p = DFS_Algorithm(cuz_state)
   print_WaysToGetGoal(p)


if __name__ == "__main__":
   main()
