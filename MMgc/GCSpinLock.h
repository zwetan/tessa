/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __GCSpinLock__
#define __GCSpinLock__

namespace MMgc
{
    /**
     * GCAcquireSpinlock is a convenience class which acquires
     * the specified spinlock at construct time, then releases
     * the spinlock at desruct time.  The single statement
     *
     *    GCAcquireSpinlock acquire(spinlock);
     *
     * ... will acquire the spinlock at the top of the function
     * and release it at the end.  This makes for less error-prone
     * code than explicit acquire/release.
     */
    class GCAcquireSpinlock
    {
    public:
        REALLY_INLINE explicit GCAcquireSpinlock(vmpi_spin_lock_t *spinlock) :
            m_spinlock(spinlock)
        {
        #ifdef _DEBUG
            bool r =
        #endif
            VMPI_lockAcquire(m_spinlock);

            GCAssert(r);
        }

        REALLY_INLINE ~GCAcquireSpinlock()
        {
        #ifdef _DEBUG
            bool r =
        #endif
            VMPI_lockRelease(m_spinlock);

            GCAssert(r);
        }

    private:
        vmpi_spin_lock_t *m_spinlock;

    private: // not implemented
        GCAcquireSpinlock();
        GCAcquireSpinlock(const GCAcquireSpinlock&);
        GCAcquireSpinlock& operator=(const GCAcquireSpinlock&);
    };

    class GCAcquireSpinlockWithRecursion
    {
    public:
        REALLY_INLINE explicit GCAcquireSpinlockWithRecursion(vmpi_spin_lock_t *sl, vmpi_thread_t owner)
            : m_spinlock(sl)
        {
            if(!VMPI_lockTestAndAcquire(sl)) {
                if(VMPI_currentThread() == owner) {
                    m_spinlock = NULL;
                } else {
                    VMPI_lockAcquire(sl);
                }
            }
        }

        ~GCAcquireSpinlockWithRecursion()
        {
            if(m_spinlock)
                VMPI_lockRelease(m_spinlock);
        }

    private:
        vmpi_spin_lock_t *m_spinlock;

    private: // not implemented
        GCAcquireSpinlockWithRecursion();
        GCAcquireSpinlockWithRecursion(const GCAcquireSpinlockWithRecursion&);
        GCAcquireSpinlockWithRecursion& operator=(const GCAcquireSpinlockWithRecursion&);
    };
}

#endif /* __GCSpinLock__ */
