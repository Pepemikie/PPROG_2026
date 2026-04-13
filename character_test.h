/** 
 * @brief Declara los tests para el módulo Character
 * @file character_test.h
 * @author Jorge Garcia Garrido
 * @date 15-03-2026
 */

#ifndef CHARACTER_TEST_H
#define CHARACTER_TEST_H

/**
 * @test Prueba la creación de un personaje
 * @pre ID del personaje
 * @post Puntero no nulo al personaje
 */
void test1_character_create();
void test2_character_create();

/**
 * @test Prueba el nombre del personaje
 */
void test1_character_set_name();
void test2_character_set_name();
void test1_character_get_name();
void test2_character_get_name();

/**
 * @test Prueba la vida del personaje
 */
void test1_character_set_health();
void test2_character_set_health();
void test1_character_get_health();
void test2_character_get_health();

/**
 * @test Prueba la amistad del personaje
 */
void test1_character_set_friendly();
void test2_character_set_friendly();
void test1_character_is_friendly();
void test2_character_is_friendly();

/**
 * @test Prueba los mensajes del personaje
 */
void test1_character_set_message();
void test2_character_set_message();
void test1_character_get_message();
void test2_character_get_message();

/**
 * @test Prueba la localización del personaje
 */
void test1_character_set_location();
void test1_character_get_location();

#endif