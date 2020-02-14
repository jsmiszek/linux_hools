cmake_minimum_required(VERSION 3.5)

project(klient LANGUAGES C)

add_executable(klient klient.c klient.h ../potomek/potomek.c ../potomek/potomek.h ../arbiter/arbiter.c ../arbiter/arbiter.h)