#ifndef NOTICE_H
#define NOTICE_H

#include <string>

/**
 * @brief Enumerates the categories of notice EventControl can broadcast.
 *
 * Includes ordinary operational changes (OPEN, CLOSE, SCHEDULE_CHANGE),
 * capacity-related changes (CAPACITY_ALERT), and safety-related changes
 * (WEATHER_ALERT, PAUSE, RESUME, EVACUATE), satisfying the requirement
 * for at least one of each category.
 */

 enum class NoticeType{
    OPEN,
    CLOSE,
    SCHEDULE_CHANGE,
    CAPACITY_ALERT,
    WEATHER_ALERT,
    PAUSE,
    RESUME,
    EVACUATE,
    CUSTOM
 };

 /**
 * @brief A single notice broadcast through the Observer system.
 *
 * Lightweight, copyable value type. Under this design's push model,
 * the full Notice is passed by const-reference to Observer::update(),
 * so observers never need to query the Subject for extra state.
 */

 struct Notice
 {
    NoticeType type;
    std::string description;
    int severity =0; //<optional payload, for exmaple capacity percentage or wind speed
    Notice(NoticeType t, std::string desc, int sev = 0)
        : type(t), description(std::move(desc)), severity(sev) {}
 };

 #endif
