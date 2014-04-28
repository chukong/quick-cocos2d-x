#!/bin/bash

git diff develop --name-only | xargs zip develop.zip {}
