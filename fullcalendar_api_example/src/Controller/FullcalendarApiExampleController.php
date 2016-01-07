<?php
/**
 * @file
 * Contains \Drupal\fullcalendar_api_example\Controller\FullcalendarApiExampleController.
 */

namespace Drupal\fullcalendar_api_example\Controller;

use Drupal\Core\Controller\ControllerBase;

/**
 * Provides route responses for the Example module.
 */
class FullcalendarApiExampleController extends ControllerBase {

  /**
   * Builds the fullcalendar/calendar example page.
   */
  public function calendar() {
    // Array of FullCalendar settings.
    $settings = array(
      'header' => array(
        'left' => 'prev,next today',
        'center' => 'title',
        'right' => 'month,agendaWeek,agendaDay',
      ),
      'defaultDate' => '2015-02-12',
      'editable' => TRUE,
      'eventLimit' => TRUE, // allow "more" link when too many events
      'events' => array(
        array(
          'title' => 'All Day Event',
          'start' => '2015-02-01',
        ),
        array(
          'title' => 'Long Event',
          'start' => '2015-02-07',
          'end' => '2015-02-10',
        ),
        array(
          'id' => 999,
          'title' => 'Repeating Event',
          'start' => '2015-02-09T16:00:00',
        ),
        array(
          'id' => 999,
          'title' => 'Repeating Event',
          'start' => '2015-02-16T16:00:00',
        ),
        array(
          'title' => 'Conference',
          'start' => '2015-02-11',
          'end' => '2015-02-13',
        ),
        array(
          'title' => 'Meeting',
          'start' => '2015-02-12T10:30:00',
          'end' => '2015-02-12T12:30:00',
        ),
        array(
          'title' => 'Lunch',
          'start' => '2015-02-12T12:00:00',
        ),
        array(
          'title' => 'Meeting',
          'start' => '2015-02-12T14:30:00',
        ),
        array(
          'title' => 'Happy Hour',
          'start' => '2015-02-12T17:30:00',
        ),
        array(
          'title' => 'Dinner',
          'start' => '2015-02-12T20:00:00',
        ),
        array(
          'title' => 'Birthday Party',
          'start' => '2015-02-13T07:00:00',
        ),
        array(
          'title' => 'Click for Google',
          'url' => 'http://google.com/',
          'start' => '2015-02-28',
        )
      )
    );

    return array(
      '#theme' => 'fullcalendar_calendar',
      '#calendar_id' => 'fullcalendar',
      '#calendar_settings' => $settings,
    );
  }
}
