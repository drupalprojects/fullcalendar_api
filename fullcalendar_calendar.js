/**
 * @file
 * Loads the full calendar.
 */

(function($) {
  Drupal.behaviors.fullCalendarApiDemo = {
    attach: function(context, settings) {

      var $calendar = $('#fullcalendar');
      if (!$calendar.length || !settings.fullcalendar_api.calendarSettings) {
        return;
      }
      $calendar.fullCalendar(settings.fullcalendar_api.calendarSettings);
      
    } 
  }
})(jQuery);
