#include <cairo.h>
#include <gtk/gtk.h>

static void
do_drawing (cairo_t *);

struct {
  int count;
  double coordx[100];
  double coordy[100];
} glob;

static gboolean
on_draw_event (GtkWidget *widget,
               cairo_t *cr,
               gpointer user_data)
{
  do_drawing (cr);

  return FALSE;
}

static void
do_drawing (cairo_t *cr)
{
  cairo_set_line_width (cr, 10);

  cairo_set_line_cap (cr, CAIRO_LINE_CAP_BUTT);
  cairo_move_to (cr, 30, 50);
  cairo_line_to (cr, 150, 50);
  cairo_stroke (cr);

  cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
  cairo_move_to (cr, 30, 90);
  cairo_line_to (cr, 150, 90);
  cairo_stroke (cr);

  cairo_set_line_cap (cr, CAIRO_LINE_CAP_SQUARE);
  cairo_move_to (cr, 30, 130);
  cairo_line_to (cr, 150, 130);
  cairo_stroke (cr);

  cairo_set_line_width (cr, 1.5);

  cairo_move_to (cr, 30, 40);
  cairo_line_to (cr, 30, 140);
  cairo_stroke (cr);

  cairo_move_to (cr, 150, 40);
  cairo_line_to (cr, 150, 140);
  cairo_stroke (cr);

  cairo_move_to (cr, 155, 40);
  cairo_line_to (cr, 155, 140);
  cairo_stroke (cr);
}

static gboolean
clicked (GtkWidget *widget,
         GdkEventButton *event,
         gpointer user_data)
{
  if (event->button == 1)
  {
    glob.coordx[glob.count] = event->x;
    glob.coordy[glob.count++] = event->y;
  }

  if (event->button == 3)
  {
    gtk_widget_queue_draw (widget);
  }

  return TRUE;
}

int
main (int argc,
      char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  glob.count = 0;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new ();
  gtk_container_add (GTK_CONTAINER (window), darea);

  gtk_widget_add_events (window, GDK_BUTTON_PRESS_MASK);

  g_signal_connect (G_OBJECT (darea), "draw", G_CALLBACK (on_draw_event), NULL);
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (window, "button-press-event", G_CALLBACK (clicked), NULL);

  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 300);
  gtk_window_set_title (GTK_WINDOW (window), "Line caps");

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
