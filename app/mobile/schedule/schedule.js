const moment = require('moment');

const Schedule = function (schedule) {
  function sessionsAscendingOrder(s1, s2) {
    if (s1.startTime.isBefore(s2.startTime)) return -1;
    else                                     return 1;
  }

  function makeSessionSummary(courseNames) {
    return (session) => {
      const s = Object.assign({}, session);

      s.courseNames = courseNames;

      return s;
    };
  }

  function availableSessions(courses) {
    const availableSessions = courses.reduce((acc, course) => {
      return acc.concat(course.sessions.map(makeSessionSummary(course.names)));
    }, []).sort(sessionsAscendingOrder);

    function currentSession(sessions) {
      return (currentTime) => {
        const currentTimeIsSessionTime = (s) =>
          currentTime.isSameOrAfter(s.startTime) &&
          currentTime.isBefore(s.endTime);

        return sessions.filter(currentTimeIsSessionTime)[0];
      };
    }

    function remainingSessions(sessions) {
      return (currentTime) => sessions.filter(session =>
        session.endTime.isAfter(currentTime));
    }

    function remainingMinutes(sessions) {
      return (currentTime) =>
        remainingSessions(sessions)(currentTime)
          .map(session => session.minutesDuration)
          .reduce((a, b) => a + b)
    }

    function minutesToNextSession(sessions) {
      return (currentTime) => {
        const minutesDiffs = remainingSessions(sessions)(currentTime)
          .sort(sessionsAscendingOrder)
          .map(s => s.startTime.diff(currentTime, 'minutes'))
          .filter(m => m > 0);

        const minDifference = (acc, e) => Math.min(acc, e);

        if (minutesDiffs.length > 0)
          return minutesDiffs.reduce(minDifference);
        else
          return NaN;
      }
    }

    return {
      available:            availableSessions,
      current:              currentSession(availableSessions),
      remaining:            remainingSessions(availableSessions),
      remainingMinutes:     remainingMinutes(availableSessions),
      minutesToNextSession: minutesToNextSession(availableSessions)
    };
  }

  function weekdayCourses(weekday) {
    function isSessionScheduled(session) {
      return session.weekday === weekday;
    }

    const courses = schedule.reduce((acc, course) => {
      const scheduledSessions = course.sessions.filter(isSessionScheduled);

      if (scheduledSessions.length > 0) {
        acc.push({
          names:    course.names,
          sessions: scheduledSessions
        });
      }

      return acc;
    }, []);

    return {
      courses:  courses,
      sessions: availableSessions(courses)
    };
  }

  return {
    weekdayCourses
  };
};

function loadSchedule(schedule) {
  const toMoment = (str) => moment(str, ['H:m']);

  return schedule.map(course => {
    const sessions = course.sessions.map(session => {
      const s = Object.assign({}, session);

      s.startTimeStr    = s.startTime;
      s.endTimeStr      = s.endTime;
      s.startTime       = toMoment(s.startTime);
      s.endTime         = toMoment(s.endTime);
      s.minutesDuration = s.endTime.diff(s.startTime, 'minutes');

      return s;
    });

    return {
      names: {
        short: course.shortName,
        long:  course.longName
      },
      sessions: sessions
    };
  });
}

module.exports = (schedule) => Schedule(loadSchedule(schedule));
