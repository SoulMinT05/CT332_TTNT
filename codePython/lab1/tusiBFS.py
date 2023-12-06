# import sys
num_tusi = 3
num_quy = 3
Maxlength = 100
# hang chuoi de in cac hanh dong
action = ["First State", "Chuyển 1 tu sĩ", "Chuyển 1 quỷ", "Chuyển 2 tu sĩ", "Chuyển 2 quỷ", "Chuyển 1 tu sĩ, 1 quỷ"]


class State:
 def __init__(self, so_tusi, so_quy, vitri_thuyen):
     self.so_tusi = so_tusi
     self.so_quy = so_quy
     self.vitri_thuyen = vitri_thuyen




def makeNullState(state):
 state.so_tusi = num_tusi
 state.so_quy = num_quy




def print_State(state: State):
  if(state.vitri_thuyen == 'A'):
     print("  A: {} tu sĩ, {} quỷ --- Thuyền đang ở bờ A --- B: {} tu sĩ, {} quỷ".format(state.so_tusi, state.so_quy,
                                                                                  num_tusi - state.so_tusi, num_quy - state.so_quy))
  else:
      print("  A: {} tu sĩ, {} quỷ --- Thuyền đang ở bờ B --- B: {} tu sĩ, {} quỷ".format(state.so_tusi, state.so_quy,
                                                                                  num_tusi - state.so_tusi, num_quy - state.so_quy))




def goalcheck(state):
 return state.so_tusi == 3 and state.so_quy == 3 and state.vitri_thuyen == 'A'




def moveOnePriest(cuz_state, result):
  if(cuz_state.vitri_thuyen == 'A'):
      if(cuz_state.so_tusi >=1 ):
          result.so_tusi = cuz_state.so_tusi - 1
          result.so_quy = cuz_state.so_quy
          result.vitri_thuyen = 'B'
          return 1
      return 0
  elif(cuz_state.so_tusi == num_tusi):
          return 0
  else:
          result.so_tusi = cuz_state.so_tusi + 1
          result.so_quy = cuz_state.so_quy
          result.vitri_thuyen = 'A'
          return 1








def moveOneDevil(cuz_state, result):
  if (cuz_state.vitri_thuyen == 'A'):
      if (cuz_state.so_quy >= 1):
          result.so_quy = cuz_state.so_quy - 1
          result.so_tusi = cuz_state.so_tusi
          result.vitri_thuyen = 'B'
          return 1
      return 0
  elif (cuz_state.so_quy == num_quy):
      return 0
  else:
      result.so_quy = cuz_state.so_quy + 1
      result.so_tusi = cuz_state.so_tusi
      result.vitri_thuyen = 'A'
      return 1




def moveTwoPriest(cuz_state, result):
  if(cuz_state.vitri_thuyen == 'A'):
      if(cuz_state.so_tusi >=2 ):
          result.so_tusi = cuz_state.so_tusi-2
          result.so_quy = cuz_state.so_quy
          result.vitri_thuyen = 'B'
          return 1
      return 0
  elif(cuz_state.so_tusi > num_tusi - 2):
      return 0
  else:
          result.so_tusi = cuz_state.so_tusi + 2
          result.so_quy = cuz_state.so_quy
          result.vitri_thuyen = 'A'
          return 1




def moveTwoDevil(cuz_state, result):
  if(cuz_state.vitri_thuyen == 'A'):
      if(cuz_state.so_quy >=2):
          result.so_quy = cuz_state.so_quy-2
          result.so_tusi = cuz_state.so_tusi
          result.vitri_thuyen = 'B'
          return 1
      return 0
  elif(cuz_state.so_quy > num_quy - 2):
      return 0
  else:
          result.so_quy = cuz_state.so_quy + 2
          result.so_tusi = cuz_state.so_tusi
          result.vitri_thuyen = 'A'
          return 1




def moveOnePriestOneDevil(cuz_state, result):
  if(cuz_state.vitri_thuyen == 'A'):
      if((cuz_state.so_tusi >=1 and cuz_state.so_quy>=1)):
          result.so_tusi = cuz_state.so_tusi -1
          result.so_quy = cuz_state.so_quy -1
          result.vitri_thuyen = 'B'
          return 1
      return 0
  elif(cuz_state.so_tusi == num_tusi or cuz_state.so_quy == num_quy):
      return 0
  else:
          result.so_tusi = cuz_state.so_tusi+1
          result.so_quy = cuz_state.so_quy + 1
          result.vitri_thuyen = 'A'
          return 1








def check(cuz_state):
  if(cuz_state.so_tusi >0 and cuz_state.so_tusi < num_tusi):
      if(cuz_state.so_tusi >= cuz_state.so_quy and num_tusi - cuz_state.so_tusi >= num_quy - cuz_state.so_quy):
              return 0
      if(cuz_state.so_tusi == num_tusi):
          if(cuz_state.so_tusi >= cuz_state.so_quy):
              return 0
      if(cuz_state.so_tusi ==0):
          if(num_tusi >= num_quy - cuz_state.so_quy):
              return 0
      return 1




def call_operator(cuz_state, result, option):
 switcher = {
     1: moveOnePriest,
     2: moveOneDevil,
     3: moveTwoPriest,
     4: moveTwoDevil,
     5: moveOnePriestOneDevil
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
 return (A.so_tusi == B.so_tusi) and (A.so_quy == B.so_quy) and (A.vitri_thuyen == B.vitri_thuyen)


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
     for opt in range(1, 5):
         newstate = State(0,0,0)
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
 cuz_state = State(0, 0, 'B')
 p = BFS_Algorithm(cuz_state)
 print_WaysToGetGoal(p)


if __name__ == "__main__":
 main()
