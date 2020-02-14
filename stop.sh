#!/bin/bash

kill $(ps e | grep 'klient' | awk '{print $1}')
kill $(ps e | grep 'serwer' | awk '{print $1}')
