const moment = require('moment');

const Client           = require('../io/client.js');
const SummaryResponses = require('../responses/summary-responses.js');

function handleSummaryRequest(Schedule, currentTime) {
  const sessions = Schedule.weekdayCourses(currentTime.day()).sessions;
  const response = SummaryResponses.makeSummaryResponse(sessions, currentTime);

  return Client.sendSummary(response);
}

module.exports = {
  handleSummaryRequest
};
