const assert = require('chai').assert;
const moment = require('moment');

const scheduleJson     = require('../schedule.json');
const Schedule         = require('mobile/schedule/schedule.js')(scheduleJson);
const SummaryResponses = require('mobile/responses/summary-responses.js');

describe('SummaryResponses#makeSummaryResponse', function test() {
  it('should yield a correct SESSION_TIME summary', function() {
    const timeA =
      moment('8:40', ['HH:mm']);
    const expectedA =
      'SESSION_TIME|0/3|50|VISIO|4204|SESSION_TIME|SISINT|4206|250';
    const actualA = SummaryResponses
      .makeSummaryResponse(Schedule.weekdayCourses(1).sessions, timeA);

    const timeB =
      moment('17:20', ['HH:mm']);
    const expectedB =
      'SESSION_TIME|2/3|30|VERISOFT|4203|GO_HOME_TIME';
    const actualB = SummaryResponses
        .makeSummaryResponse(Schedule.weekdayCourses(1).sessions, timeB);

    assert.equal(expectedA, actualA);
    assert.equal(expectedB, actualB);
  });

  it('should yield a correct BREAK_TIME summary', function test() {
    const time =
      moment('9:30', ['HH:mm']);
    const expected =
      'BREAK_TIME|1/3|200|SISINT|4206';
    const actual = SummaryResponses
        .makeSummaryResponse(Schedule.weekdayCourses(1).sessions, time);

    assert.equal(expected, actual);
  });

  it('should yield a correct GO_HOME_TIME summary', function test() {
    const time =
      moment('23:30', ['HH:mm']);
    const expected =
      'GO_HOME_TIME|3/3';
    const actual = SummaryResponses
        .makeSummaryResponse(Schedule.weekdayCourses(1).sessions, time);

    assert.equal(expected, actual);
  });

  it('should yiled a correct FREE_TIME summary', function test() {
    const time = moment('11:20', ['HH:mm']);

    const expected = 'FREE_TIME';
    const actual = SummaryResponses
      .makeSummaryResponse(Schedule.weekdayCourses(6).sessions, time);

    assert(expected, actual);
  });
});
