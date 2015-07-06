<?php

/**
 * @file
 * Callbacks for FullCalendar API Examples feeds.
 */

/**
 * Ajax deliver callback for /fullcalendar/json-data.
 */
function full_calendar_api_example_data_provider() {
  echo drupal_json_encode(array(
    'test1' => 'test2',
  ));
  drupal_exit();
}
