
#ifndef _GENC_HASH_MAP_H
#define _GENC_HASH_MAP_H

#include <stdlib.h>
#include "genc_List.h"

#define GENC_HASH_MAP_ELEMENT(type) \
struct \
{ \
    unsigned char* key; \
    size_t key_length; \
    GENC_LIST_ELEMENT(type); \
} genc_HashMap_element

#define GENC_HASH_MAP_ELEMENT_INIT(hmap) \
GENC_LIST_ELEMENT_INIT(&((hmap)->genc_HashMap_element))

#define GENC_HASH_MAP_ELEMENT_KEY(element) \
(element)->genc_HashMap_element.key

#define GENC_HASH_MAP_ELEMENT_KEY_LENGTH(element) \
(element)->genc_HashMap_element.key_length

#define GENC_HASH_MAP_ELEMENT_PREVIOUS(element) \
GENC_LIST_ELEMENT_PREVIOUS(&((element)->genc_HashMap_element))

#define GENC_HASH_MAP_ELEMENT_NEXT(element) \
GENC_LIST_ELEMENT_NEXT(&((element)->genc_HashMap_element))

#define GENC_HASH_MAP(type) \
struct { \
    type** elements; \
    size_t capacity; \
    size_t size; \
} genc_HashMap

#define GENC_HASH_MAP_INIT(hmap, _capacity) \
do { \
    (hmap)->genc_HashMap.elements = calloc(_capacity, sizeof(*((hmap)->genc_HashMap.elements))); \
    (hmap)->genc_HashMap.capacity = _capacity; \
    (hmap)->genc_HashMap.size = 0; \
} while(0)

#define GENC_HASH_MAP_INDEX(hmap, index) \
(hmap)->genc_HashMap.elements[index]

#define GENC_HASH_MAP_CAPACITY(hmap) \
(hmap)->genc_HashMap.capacity

#define GENC_HASH_MAP_SIZE(hmap) \
(hmap)->genc_HashMap.size

#define GENC_HASH_MAP_GET(hmap, _key, _key_length, element) \
do { \
    size_t hash = 0; \
    for(size_t i = 0; i < _key_length; ++i) { \
        hash += _key[i]; \
        hash << 8; \
    } \
    hash %= (hmap)->genc_HashMap.capacity; \
    element = (hmap)->genc_HashMap.elements[hash]; \
    while(element != NULL && strncmp(_key, (element)->genc_HashMap_element.key, _key_length) != 0) \
        element = GENC_HASH_MAP_ELEMENT_NEXT(element); \
} while(0)

#define GENC_HASH_MAP_REMOVE(hmap, _key, _key_length, element) \
do { \
    size_t hash = 0; \
    for(size_t i = 0; i < _key_length; ++i) { \
        hash += _key[i]; \
        hash << 8; \
    } \
    hash %= (hmap)->genc_HashMap.capacity; \
    element = (hmap)->genc_HashMap.elements[hash]; \
    while(element != NULL && strncmp(_key, (element)->genc_HashMap_element.key, _key_length) != 0) \
        element = GENC_HASH_MAP_ELEMENT_NEXT(element); \
    if(element != NULL) { \
        if(element == (hmap)->genc_HashMap.elements[hash] && GENC_HASH_MAP_ELEMENT_NEXT(element) == NULL) \
            (hmap)->genc_HashMap.elements[hash] = NULL; \
        if(GENC_HMAP_ELEMENT_PREVIOUS(element) != NULL) { \
            GENC_HASH_MAP_ELEMENT_NEXT(GENC_HASH_MAP_ELEMENT_PREVIOUS(element) = GENC_HASH_MAP_ELEMENT_NEXT(element) \
            GENC_HASH_MAP_ELEMENT_PREVIOUS(element) = NULL; \
        } \
        if(GENC_HASH_MAP_ELEMENT_NEXT(element) != NULL) { \
            GENC_HASH_MAP_ELEMENT_PREVIOUS(GENC_HASH_MAP_ELEMENT_NEXT(element) = GENC_HASH_MAP_ELEMENT_PREVIOUS(element); \
            GENC_HASH_MAP_ELEMENT_NEXT(element) = NULL; \
        } \
        --((hmap)->genc_HashMap.size); \
    } \
} while(0)

#define GENC_HASH_MAP_SET(hmap, element, oldElement) \
do { \
    size_t hash = 0; \
    for(size_t i = 0; i < (element)->genc_HashMap_element.key_length; ++i) { \
        hash += (element)->genc_HashMap_element.key[i]; \
        hash << 8; \
    } \
    hash %= (hmap)->genc_HashMap.capacity; \
    if((hmap)->genc_HashMap.elements[hash] == NULL) \
        (hmap)->genc_HashMap.elements[hash] = element; \
    else { \
        oldElement = (hmap)->genc_HashMap.elements[hash]; \
        while(oldElement != NULL && \
             strncmp((element)->genc_HashMap_element.key, (oldElement)->genc_HashMap_element.key, (element)->genc_HashMap_element.key_length) != 0) { \
            oldElement = GENC_HASH_MAP_ELEMENT_NEXT(oldElement); \
        } \
        if(oldElement != NULL) { \
            if(GENC_HASH_MAP_ELEMENT_PREVIOUS(oldElement) != NULL) { \
                GENC_HASH_MAP_ELEMENT_NEXT(GENC_HASH_MAP_ELEMENT_PREVIOUS(oldElement)) = GENC_HASH_MAP_ELEMENT_NEXT(oldElement); \
                GENC_HASH_MAP_ELEMENT_PREVIOUS(oldElement) = NULL; \
            } \
            if(GENC_HASH_MAP_ELEMENT_NEXT(oldElement) != NULL) { \
                GENC_HASH_MAP_ELEMENT_PREVIOUS(GENC_HASH_MAP_ELEMENT_NEXT(oldElement)) = GENC_HASH_MAP_ELEMENT_PREVIOUS(oldElement); \
                GENC_HASH_MAP_ELEMENT_NEXT(oldElement) = NULL; \
            } \
        } \
        else \
            ++((hmap)->genc_HashMap.size); \
        GENC_HASH_MAP_ELEMENT_NEXT(element) = (hmap)->genc_HashMap.elements[hash]; \
        GENC_HASH_MAP_ELEMENT_PREVIOUS((hmap)->genc_HashMap.elements[hash]) = element; \
        (hmap)->genc_HashMap.elements[hash] = element; \
    } \
} while(0)

#define GENC_HASH_MAP_INDEX_REMOVE(hmap, index, element) \
do { \
    element = (hmap)->genc_HashMap.elements[index]; \
    if(element != NULL) { \
        (hmap)->genc_HashMap.elements[index] = GENC_HASH_MAP_ELEMENT_NEXT(element); \
        GENC_HASH_MAP_ELEMENT_PREVIOUS(GENC_HASH_MAP_ELEMENT_NEXT(element)) = NULL; \
	GENC_HASH_MAP_ELEMENT_NEXT(GENC_HASH_MAP_ELEMENT_NEXT(element)) = GENC_HASH_MAP_ELEMENT_NEXT(element) \
	GENC_HASH_MAP_ELEMENT_PREVIOUS(element) = NULL; \
        GENC_HASH_MAP_ELEMENT_NEXT(element) = NULL; \
    } \
} while(0)

#define GENC_HASH_MAP_FREE_ELEMENTS(hmap) \
free((hmap)->genc_HashMap.elements)

#endif
