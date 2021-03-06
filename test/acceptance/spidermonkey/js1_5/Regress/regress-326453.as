/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/licenses/publicdomain/
 * Contributor: Blake Kaplan
 */
startTest();

var gTestfile = 'regress-326453.js';
//-----------------------------------------------------------------------------
var BUGNUMBER = 326453;
var summary = 'Do not assert: while decompiling';
var actual = 'No Crash';
var expect = 'No Crash';

printBugNumber(BUGNUMBER);
printStatus (summary);

function f() { with({})function g() { }; printStatus(); }

printStatus(f.toString());

AddTestCase(summary, expect, actual);

test();
