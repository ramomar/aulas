Aulas
==========

<p align="center">
   <img src="https://user-images.githubusercontent.com/10622989/28222664-1ac18fe6-688e-11e7-9d4f-35c067d47089.gif">
</p>

A simple app/watchface I made to help myself with my uni schedule.
In order to extract the schedule to be shown, I made use of one of my [scripts](https://github.com/ramomar/siase-schedule-scraper).


## Features
- Display of current session name, classroom, and remaining time.
- Display of next session name, classroom, and standby time.
- Display of finished sessions/remaining sessions of the day.
- _You can go home display_ (when there are no more classes to take).
- _No school display_ (when you can stay home doing homework 🤓).

You can see UI screenshots [here](https://github.com/ramomar/pebble-schedule/issues/1).

## Project structure
The smartphone acts as a simple server and the watch as a client. Each device has its own package in the app folder.

## Dependencies
This project mainly depends on the Pebble SDK v4.3 and npm v4.0.5.
To satisfy every extra dependency, you may run the following command:

`npm install`

## Building
In order to bundle everything and be able to deploy to end devices, you may run the following command:

`pebble build`

## Running
Your smartphone must have installed the Pebble app. After you bundle everything, you should run the following command:

`pebble install --phone x.x.x.x`

## Testing
In order to run tests, you may run the following command: 

`npm test`

## Debugging
If you want to see some useful com logs between devices, you may run the following command:

`pebble logs --phone x.x.x.x`
