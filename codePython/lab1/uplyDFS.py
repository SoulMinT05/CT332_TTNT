UP = 0
NGUA = 1
NUM_OF_CUPS = 6
ACTIONS = [
    "First state",
    "Lật ly 1 2 3",
    "Lật ly 2 3 4",
    "Lật ly 3 4 5",
    "Lật ly 4 5 6",
]


class State:
    def __init__(self):
        self.__list_cups = [UP] * NUM_OF_CUPS

    def make_null_state(self):
        for i in range(NUM_OF_CUPS):
            self.__list_cups[i] = UP

    def get_cup(self, index: int):
        return self.__list_cups[index]

    def set_cup(self, index: int, value: int):
        self.__list_cups[index] = value

    def set_list_cups(self, L: list):
        for index in range(NUM_OF_CUPS):
            self.set_cup(index, L[index])

    def print_state(self):
        for index in range(NUM_OF_CUPS):
            print(self.get_cup(index), end=" ")

    def is_goal_state(self):
        for index in range(NUM_OF_CUPS):
            if self.get_cup(index) == UP:
                return False
        return True


def compare_states(s1: State, s2: State):
    for i in range(NUM_OF_CUPS):
        if s1.get_cup(i) != s2.get_cup(i):
            return False
    return True


def find_state(state: State, L: list):
    temp_list = L.copy()
    while len(temp_list) > 0:
        if compare_states(state, temp_list[-1].get_state()):
            return 1
        temp_list.pop()
    return 0


def flip_three_cups(first_cup: int, current_state: State, result_state: State):
    for index in range(NUM_OF_CUPS):
        result_state.set_cup(index, current_state.get_cup(index))
    for index in range(first_cup, first_cup + 3):
        if current_state.get_cup(index) == NGUA:
            result_state.set_cup(index, UP)
        else:
            result_state.set_cup(index, NGUA)


class Node:
    def __init__(self):
        self.__state = State()
        self.__parent_node = None
        self.__action = 0

    def set_state(self, state: State):
        self.__state = state

    def set_parent_node(self, node):
        self.__parent_node = node

    def set_action(self, action: int):
        self.__action = action

    def get_state(self):
        return self.__state

    def get_parent_node(self):
        return self.__parent_node

    def get_action(self):
        return self.__action


def dfs(current_state: State):
    open_stack = []
    close_stack = []
    root = Node()
    root.set_state(current_state)
    root.set_parent_node(None)
    root.set_action(0)
    open_stack.append(root)
    while open_stack:
        current_node = open_stack.pop()
        close_stack.append(current_node)
        if current_node.get_state().is_goal_state():
            return current_node
        for first_cup in range(0, NUM_OF_CUPS - 2):
            new_state = State()
            new_state.make_null_state()
            flip_three_cups(first_cup, current_node.get_state(), new_state)
            if find_state(new_state, open_stack) or find_state(new_state, close_stack):
                continue
            new_node = Node()
            new_node.set_state(new_state)
            new_node.set_parent_node(current_node)
            new_node.set_action(first_cup + 1)
            open_stack.append(new_node)
    return None


def print_solution(node: Node):
    printed_stack = []
    while node.get_parent_node() != None:
        printed_stack.append(node)
        node = node.get_parent_node()
    printed_stack.append(node)
    action = 0
    while printed_stack:
        current_node = printed_stack.pop()
        print("\nAction {}: {}".format(action, ACTIONS[current_node.get_action()]))
        current_node.get_state().print_state()
        action += 1


def main():
    start_state = State()
    L = [NGUA, UP, NGUA, UP, NGUA, UP]
    start_state.set_list_cups(L)
    node = dfs(start_state)
    print_solution(node)


if __name__ == "__main__":
 main()
