<?php
/**
 * Theme implementations and template preprocess functions for 
 * FullCalendar API module.
 */

/**
 * Theme function for fullcalendar_calendar.
 *
 * @params
 *   events array of event objects
 *   date_field string field name of valid date field
 *   calendar_settings array of settings to override FullCalendar.js defaults
 */
function theme_fullcalendar_calendar($vars) {
  $user_settings = $vars['calendar_settings'];

  // Default settings.
  $settings = array(
    'header' => array(
      'left' => 'month,agendaWeek',
      'right' => 'prev title next',
    ),
    'defaultDate' => date('Y-m-d'),
    'businessHours' => TRUE,
    'editable' => TRUE,
    'events' => array(),
  );

  // Override defaults with user submitted data.
  $settings = array_replace_recursive($settings, $user_settings);

  // Add fullcalendar scripts.
  libraries_load('fullcalendar');
  drupal_add_js(drupal_get_path('module', 'fullcalendar_api') . '/fullcalendar_calendar.js');
  drupal_add_js(array('fullcalendar_api' => array('calendarSettings' => $settings)), 'setting');

  return array(
    '#markup' => '<div id="fullcalendar"></div>',
  );
}


/**
 * Theme function for fullcalendar_calendar_entity.
 * Renders an array of entities with date fields as calendar items.
 *
 * @params
 *   events array of event objects
 *   date_field string field name of valid date field
 *   calendar_settings array of settings to override FullCalendar.js defaults
 */
function theme_fullcalendar_calendar_entity($vars) {
  $events = $vars['events'];
  $date_field = $vars['date_field'];
  $settings = $vars['calendar_settings'];

  // Check if field is valid date type.
  $date_field_info = field_info_field($date_field);
  if (
    !$date_field_info ||
    !in_array($date_field_info['type'], array('date', 'datetime', 'datestamp'))
  ) {
    throw new Exception(t('Field name %field_name is not a valid date field.', array('%field_name' => $date_field)));
  }

  foreach ($events as $event) {
    $start = NULL;
    $end = NULL;

    // If the date type is not "datestamp" (timestamp), pass the string to 
    // DateTime constructor. It will automatically detect the date format and 
    // give us a timestamp.
    switch ($event->{$date_field}['und'][0]['date_type']) {
      case 'date':
      case 'datetime':
        // @todo timezone?
        $dateTime = new DateTime($event->{$date_field}['und'][0]['value']);
        $start = $dateTime->getTimestamp();

        // if end date
        if (!empty($event->{$date_field}['und'][0]['value2'])) {
          // @todo timezone?
          $endDateTime = new DateTime($event->{$date_field}['und'][0]['value2']);
          $end = $endDateTime->getTimestamp();
        }
        break;
      case 'datestamp':
        // Date value is already a timestamp.
        $start = $event->{$date_field}['und'][0]['value'];
        // if end date
        if (!empty($event->{$date_field}['und'][0]['value2'])) {
          $end = $event->{$date_field}['und'][0]['value2'];
        }
        break;
    }

    $event_array = array(
      'id' => $event->id,
      'title' => $event->title,
      'start' => date('c', $start),
    );
    if (!empty($end)) {
      $event_array['end'] = date('c', $end);
    }
    $settings['events'][] = $event_array;
  }

  // At this point validation is complete. 
  // Pass the settings data to the theme_fullcalendar_calendar function.

  return theme('fullcalendar_calendar', array('calendar_settings' => $settings));
}
