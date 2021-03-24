//
// Created by vfs on 3/21/2021.
//

typedef struct VertexList {
    Vertex *memory;
    int count;
    int size;
} VertexList;

void vertexlist_init(VertexList *vertexlist) {
    vertexlist->count = 0;
    vertexlist->size = 8;
    vertexlist->memory = malloc(vertexlist->size * sizeof(Vertex));
}

void vertexlist_grow(VertexList *vertexlist) {
    vertexlist->size *= 2;
    vertexlist->memory = realloc(vertexlist->memory, vertexlist->size * sizeof(Vertex));
}

void vertexlist_add(VertexList *vertexlist, Vertex item) {
    if (vertexlist->count < vertexlist->size - 1) {
        vertexlist->memory[vertexlist->count++] = item;
    } else {
        vertexlist_grow(vertexlist);
        vertexlist->memory[vertexlist->count++] = item;
    }
}

typedef struct Vec3List {
    vec3 *memory;
    int count;
    int size;
} Vec3List;

void vec3list_init(Vec3List *vec3list) {
    vec3list->count = 0;
    vec3list->size = 8;
    vec3list->memory = malloc(vec3list->size * sizeof(vec3));
}

void vec3list_grow(Vec3List *vec3list) {
    vec3list->size *= 2;
    vec3list->memory = realloc(vec3list->memory, vec3list->size * sizeof(vec3));
}

void vec3list_add(Vec3List *vec3list, vec3 item) {
    if (vec3list->count < vec3list->size - 1) {
        vec3list->memory[vec3list->count++] = item;
    } else {
        vec3list_grow(vec3list);
        vec3list->memory[vec3list->count++] = item;
    }
}

typedef struct Vec2List {
    vec2 *memory;
    int count;
    int size;
} Vec2List;

void vec2list_init(Vec2List *vec2list) {
    vec2list->count = 0;
    vec2list->size = 8;
    vec2list->memory = malloc(vec2list->size * sizeof(vec2));
}

void vec2list_grow(Vec2List *vec2list) {
    vec2list->size *= 2;
    vec2list->memory = realloc(vec2list->memory, vec2list->size * sizeof(vec2));
}

void vec2list_add(Vec2List *vec2list, vec2 item) {
    if (vec2list->count < vec2list->size - 1) {
        vec2list->memory[vec2list->count++] = item;
    } else {
        vec2list_grow(vec2list);
        vec2list->memory[vec2list->count++] = item;
    }
}

typedef struct IntList {
    int *memory;
    int count;
    int size;
} IntList;

void intlist_init(IntList *list) {
    list->count = 0;
    list->size = 8;
    list->memory = malloc(list->size * sizeof(int));
}

void intlist_grow(IntList *list) {
    list->size *= 2;
    list->memory = realloc(list->memory, list->size * sizeof(int));
}

void intlist_add(IntList *list, int item) {
    if (list->count < list->size - 1) {
        list->memory[list->count++] = item;
    } else {
        intlist_grow(list);
        list->memory[list->count++] = item;
    }
}
