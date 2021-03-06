// Generated from ST_mmgc_gcheap.st
// -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
//
// ***** BEGIN LICENSE BLOCK *****
// Version: MPL 1.1/GPL 2.0/LGPL 2.1
//
// The contents of this file are subject to the Mozilla Public License Version
// 1.1 (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at
// http://www.mozilla.org/MPL/
//
// Software distributed under the License is distributed on an "AS IS" basis,
// WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
// for the specific language governing rights and limitations under the
// License.
//
// The Original Code is [Open Source Virtual Machine.].
//
// The Initial Developer of the Original Code is
// Adobe System Incorporated.
// Portions created by the Initial Developer are Copyright (C) 2004-2006
// the Initial Developer. All Rights Reserved.
//
// Contributor(s):
//   Adobe AS3 Team
//
// Alternatively, the contents of this file may be used under the terms of
// either the GNU General Public License Version 2 or later (the "GPL"), or
// the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
// in which case the provisions of the GPL or the LGPL are applicable instead
// of those above. If you wish to allow use of your version of this file only
// under the terms of either the GPL or the LGPL, and not to allow others to
// use your version of this file under the terms of the MPL, indicate your
// decision by deleting the provisions above and replace them with the notice
// and other provisions required by the GPL or the LGPL. If you do not delete
// the provisions above, a recipient may use your version of this file under
// the terms of any one of the MPL, the GPL or the LGPL.
//
// ***** END LICENSE BLOCK ***** */

#include "avmshell.h"
#ifdef VMCFG_SELFTEST
namespace avmplus {
class ST_mmgc_gcheap : public Selftest {
public:
ST_mmgc_gcheap(AvmCore* core);
virtual void run(int n);
private:
static const char* ST_names[];
void test0();
void test1();
};
ST_mmgc_gcheap::ST_mmgc_gcheap(AvmCore* core)
    : Selftest(core, "mmgc", "gcheap", ST_mmgc_gcheap::ST_names)
{}
const char* ST_mmgc_gcheap::ST_names[] = {"largeAlloc","largeAllocAlignment", NULL };
void ST_mmgc_gcheap::run(int n) {
switch(n) {
case 0: test0(); return;
case 1: test1(); return;
}
}
using namespace MMgc;

void ST_mmgc_gcheap::test0() {
       GCHeap *heap = GCHeap::GetGCHeap();
       for(int i=1;i<4;i++) {
       	  void *item = heap->Alloc(GCHeap::kOSAllocThreshold*i);
#line 50 "ST_mmgc_gcheap.st"
verifyPass(heap->Size(item) == GCHeap::kOSAllocThreshold*i, "heap->Size(item) == GCHeap::kOSAllocThreshold*i", __FILE__, __LINE__);
          heap->Free(item);
       }
#line 53 "ST_mmgc_gcheap.st"
verifyPass(true, "true", __FILE__, __LINE__);

}
void ST_mmgc_gcheap::test1() {
       GCHeap *heap = GCHeap::GetGCHeap();
       for(int i=1;i<10;i++) {
       	  void *item = heap->Alloc(GCHeap::kOSAllocThreshold*i, GCHeap::flags_Alloc, 1<<i);
#line 59 "ST_mmgc_gcheap.st"
verifyPass(heap->Size(item) == GCHeap::kOSAllocThreshold*i, "heap->Size(item) == GCHeap::kOSAllocThreshold*i", __FILE__, __LINE__);
#line 60 "ST_mmgc_gcheap.st"
verifyPass(uintptr_t(((GCHeap::kBlockSize<<(i-1))-1) & uintptr_t(item)) == 0, "uintptr_t(((GCHeap::kBlockSize<<(i-1))-1) & uintptr_t(item)) == 0", __FILE__, __LINE__);
	      heap->Free(item);
       }


}
void create_mmgc_gcheap(AvmCore* core) { new ST_mmgc_gcheap(core); }
}
#endif
