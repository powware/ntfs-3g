/* uefi_bridge.c - libntfs-3g interface for UEFI */
/*
 *  Copyright © 2021 Pete Batard <pete@akeo.ie>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "compat.h"
#include "logging.h"

#include "uefi_driver.h"
#include "uefi_bridge.h"
#include "uefi_logging.h"
#include "uefi_support.h"

/*
 * Translate a UEFI driver log level into a libntfs-3g log level.
 */
VOID
NtfsSetLogger(UINTN Level)
{
	/* Critical log level is always enabled */
	UINT32 levels = NTFS_LOG_LEVEL_CRITICAL;

	if (Level >= FS_LOGLEVEL_ERROR)
		levels |= NTFS_LOG_LEVEL_ERROR | NTFS_LOG_LEVEL_PERROR;
	if (Level >= FS_LOGLEVEL_WARNING)
		levels |= NTFS_LOG_LEVEL_WARNING;
	if (Level >= FS_LOGLEVEL_INFO)
		levels |= NTFS_LOG_LEVEL_INFO | NTFS_LOG_LEVEL_VERBOSE | NTFS_LOG_LEVEL_PROGRESS;
	if (Level >= FS_LOGLEVEL_DEBUG)
		levels |= NTFS_LOG_LEVEL_DEBUG | NTFS_LOG_LEVEL_QUIET;
	if (Level >= FS_LOGLEVEL_EXTRA)
		levels |= NTFS_LOG_LEVEL_TRACE;

	ntfs_log_clear_flags(UINT32_MAX);
	/* If needed, NTFS_LOG_FLAG_FILENAME | NTFS_LOG_FLAG_LINE can be added */
	ntfs_log_set_flags(NTFS_LOG_FLAG_PREFIX);
	ntfs_log_clear_levels(UINT32_MAX);
	ntfs_log_set_levels(levels);
}