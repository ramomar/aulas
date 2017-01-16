static unsigned int counter = 0;

unsigned int remaining_minutes() {
  return counter;
}

unsigned int set_remaining_minutes(unsigned int minutes) {
  counter = minutes;
  return counter;
}

unsigned int remaining_minutes_tick() {
  if (counter == 0) {
    return counter;
  }
  else {
    counter-=1;
    return counter;
  }
}
