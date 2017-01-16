const moment = require('moment');

/*
  Mini hacks so I don't have to deal with same times different dates,
  will refactor later ;(
*/
function minutesDiff(t1, t2) {
  const t22 = t1.clone();

  t22.hours(t2.hours());
  t22.minutes(t2.minutes());

  return t22.diff(t1, 'minutes');
}

function respondSummaryRequest(sessions, client, currentTime) {
  const currentSession           = sessions.current(currentTime);
  const totalSessions            = sessions.available.length;
  const remainingSessions        = sessions.remaining(currentTime).length;
  const minutesLeftToNextSession = sessions.minutesToNextSession(currentTime);

  let nextSession = sessions
    .current(currentTime.clone().add(minutesLeftToNextSession, 'minutes'));

  if (!nextSession) {
    nextSession = {
      courseNames: {short: '(:'},
      classroom: '...'
    };
  }

  function makeSummary() {
    const completedSessions = totalSessions - remainingSessions;

    if (remainingSessions == 0 || sessions.available.length == 0) {
      return 'FREE_TIME';
    }
    else if (!currentSession && remainingSessions > 0) {
      const sessionTime =
        // We add one minute because I'm a paranoid dude
        // lol joking, this fixes weird bug in mobile (PC is ok)
        currentTime.clone().add(minutesLeftToNextSession+1, 'minutes');
      const session = sessions.current(sessionTime);

      // Summary example: 'BREAK_TIME|2/3|120|AUTO|4201
      return [
        'BREAK_TIME',
        `${completedSessions}/${totalSessions}`,
        minutesDiff(
          currentTime.clone(),
          session.startTime.clone()
        ),
        `${session.courseNames.short} ${session.classroom}`
      ].join('|');
    }
    else {
      // Summary example: 'SESSION_TIME|2/3|50|RED|2304|AUTO|4201'
      return [
        'SESSION_TIME',
        `${completedSessions}/${totalSessions}`,
        minutesDiff(
          currentTime.clone(),
          currentSession.endTime.clone()
        ),
        currentSession.courseNames.short,
        currentSession.classroom,
        `${nextSession.courseNames.short} ${nextSession.classroom}`
      ].join('|');
    }
  }

  return client.sendSummary(makeSummary());
}

module.exports = function (Schedule, client, currentTime, weekday) {
  const sessions = Schedule.weekdayCourses(weekday).sessions;

  return {
    handleSummaryRequest: () =>
      respondSummaryRequest(sessions, client, currentTime)
  };
};
