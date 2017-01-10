const assert = require('chai').assert;
const moment = require('moment');

const scheduleJson = require('./schedule.json');
const Schedule     = require('js/schedule/schedule.js')(scheduleJson);

describe('Schedule#weekdayCourses', function test() {

  it('should yield the courses for a given weekday', function() {
    const expected = ['VISIO', 'SISINT', 'VERISOFT'];
    const actual = Schedule.weekdayCourses(1).courses.map(c => c.names.short);

    assert.sameMembers(actual, expected);
  });
});

describe('Courses#Sessions#current', function test() {

  it('should yield the current session for a given time', function() {
    const time = moment('7:00', ['H:m']);

    const expected = {
      courseNames: {
        short:  'RED',
        long: 'REDES DE TELECOMUNICACIONES'
      },
      weekday:      2,
      turn:         1,
      group:        '002',
      classroom:    '4204',
      startTimeStr: '7:00',
      endTimeStr:   '7:50'
    };
    const actual = Schedule.weekdayCourses(2).sessions.current(time);

    assert.equal(actual.courseNames.short, expected.courseNames.short);
    assert.equal(actual.weekday, expected.weekday);
    assert.equal(actual.turn, expected.turn);
    assert.equal(actual.startTimeStr, expected.startTimeStr);
  });
});

describe('Courses#Sessions#total', function test() {
  it ('should yield the number of sessions for the day', function () {
    const expected = 3;
    const actual = Schedule.weekdayCourses(1).sessions.total;

    assert.equal(actual, expected);
  });
});

describe('Courses#Sessions#remainingCount', function test() {
  it ('should yield the number of remaining sessions for the day given a time',
    function () {
      const time1 = moment('9:29', ['H:m']);

      const expected1 = 3;
      const actual1   = Schedule
        .weekdayCourses(1)
        .sessions
        .remainingCount(time1);

      const time2 = moment('9:30', ['H:m']);

      const expected2 = 2;
      const actual2   = Schedule
        .weekdayCourses(1)
        .sessions.remainingCount(time2);

      assert.equal(actual1, expected1);
      assert.equal(actual2, expected2);
    });
});

describe('Courses#Sessions#remaining', function test() {
  it ('should yield the remaining sessions for the day given a time',
    function () {
      const time = moment('9:30', ['H:m']);

      const expected = ['SISINT', 'VERISOFT'];
      const actual   = Schedule
        .weekdayCourses(1)
        .sessions
        .remaining(time)
        .map(s => s.courseNames.short);

      assert.sameMembers(actual, expected);
    });
});

describe('Courses#Sessions#remainingMinutes', function test() {
  it ('should yield the remaining minutes of sessions for the day given a time',
    function () {
      const time1 = moment('9:29', ['H:m']);

      const expected1 = 150;
      const actual1   = Schedule
        .weekdayCourses(1)
        .sessions
        .remainingMinutes(time1);

      const time2 = moment('9:30', ['H:m']);

      const expected2 = 100;
      const actual2   = Schedule
        .weekdayCourses(1)
        .sessions.remainingMinutes(time2);

      assert.equal(actual1, expected1);
      assert.equal(actual2, expected2);
    });
});
