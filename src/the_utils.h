#ifndef THE_UTILS_H
#define THE_UTILS_H

#include <QString>

/**
 * Utility functions used across HTVP
 */
namespace TheUtils {
/**
 * @brief gets the icon file path from a video file path
 * @param the video path
 * @return the icon path
 */
QString getIconPathFromVideoPath(const QString videoPath);

/**
 * @brief checks if the filename is a valid video for the correspoinding OS
 * @param the video path
 * @return true if valid, else false
 */
bool filenameIsValidVideo(const QString videoPath);

/**
 * @brief returns true if the current OS is windows
 * @return true if on windows, else false
 */
bool isWindows();

/**
 * @brief returns true if the current OS is linux
 * @return true if on linux, else false
 */
bool isLinux();

/**
 * @brief prettify timestamps
 *
 * example: 60,000 -> 01:00
 *
 * @param time in milliseconds
 * @return formatted timestamps
 */
QString prettyTime(qint64 time);
} // namespace TheUtils

#endif // THE_UTILS_H
