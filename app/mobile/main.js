const Client          = require('mobile/io/client.js');
const SummaryHandling = require('mobile/summary-handling.js');

function handleAppMessage(msg) {
  if (msg.payload['Summary']) {
    SummaryHandling.handleSummaryRequest();
  }
}

Pebble.addEventListener('ready', () => {
  Client.sendMobileReady(() => SummaryHandling.respondSummaryRequest());
});

Pebble.addEventListener('appmessage', handleAppMessage);
