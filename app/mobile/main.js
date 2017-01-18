const AppHandlers = require('./handlers/app-handlers.js');

Pebble.addEventListener('ready', () => {
  console.info('Phone is ready.');
  AppHandlers.handleMobileReady();
});

Pebble.addEventListener('appmessage', (message) => {
  console.info('Got message: ' + JSON.stringify(message));
  AppHandlers.handleAppMessage(message);
});
