/**
 * @file
 * Loads the full calendar.
 */

(function($) {
  Drupal.behaviors.fullCalendarApiCalendar = {
    attach: function(context, settings) {

      var $calendar = $('#fullcalendar');
      if (!$calendar.length || !settings.fullcalendar_api.calendarSettings) {
        return;
      }
      var $settings = settings.fullcalendar_api.calendarSettings;
      // Merge in event callbacks.
      $.extend($settings, {
        eventDrop: function(event, delta, revertFunc) {

          // Create a simple object to send to ajax function.
          var $data = {
            id: event.id,
            title: event.title,
            entityType: event.entityType ? event.entityType : null,
            bundle: event.bundle ? event.bundle : null,
            allDay: event.allDay,
            dateField: event.dateField,
            startTime: event.start.unix(),
            endTime: event.end ? event.end.unix() : null
          };

          if (!confirm("Are you sure about this change?")) {
            revertFunc();
          }
          else {
            // Save the entity via AJAX.
            $.ajax({
              method: 'POST',
              url: '//' + window.location.hostname +  settings.basePath + settings.pathPrefix + 'fullcalendar-api/ajax/update/drop/' + event.id,
              data: $data
            }).done(function(response){
              // @todo return success?
              if (response == 'failure') {
                revertFunc();
              }
            });
          }

        }
      });
      
      $calendar.fullCalendar($settings);
    } 
  }
})(jQuery);
