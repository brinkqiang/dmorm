#!/bin/sh
python generate_fsm.py htmlparser_fsm.config > htmlparser_fsm.h
python generate_fsm.py jsparser_fsm.config > jsparser_fsm.h