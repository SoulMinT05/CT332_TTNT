 find_State(State state, List list, int *position) {
    int i;
    for(i=1; i<=list.size; i++)
        if(compareStates(element_at(i, list)->state, state)) {
            *position = i;
            return element_at(i, list);
        }
    return NULL;