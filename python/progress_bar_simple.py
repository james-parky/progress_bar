'''Single function import for creating custom progress_bar'''

__author__ = "James Parkington"
__license__ = "Public Domain"
__version__ = "1.3"

_TARGET_COLOUR = '\33[31m'
_BASE_COLOUR = '\33[0m'
_FILLED_TICK = '█'
_EMPTY_TICK = '-'


def draw_progress_bar(increment: int = 2,
                      target: int = 100,
                      percentage: int = 0,
                      annotation: bool = True):
    '''Print the progress bar to terminal'''
    if increment not in [1, 2, 5]:
        raise ValueError('Increment must be equal to 1, 2 or 5.')

    if not (isinstance(target, int) and 0 <= target <= 100):
        raise ValueError('Target must be an integer in the range 0-100.')

    if not isinstance(annotation, bool):
        raise TypeError('Annotation must be of type \'bool\'.')

    if not(isinstance(percentage, int) and 0 <= percentage <= 100):
        raise ValueError(
            'Percentage must be an integer in the range 0-100.')

    rounded_percentage = percentage - (percentage % increment)
    num_filled_ticks = rounded_percentage // increment
    num_empty_ticks = 100//increment - num_filled_ticks

    progress_bar = [_FILLED_TICK]*num_filled_ticks + ['-']*num_empty_ticks

    rounded_target = target - (target % increment)
    progress_bar[(rounded_target //
                 increment)-1] = f'{_TARGET_COLOUR}{_FILLED_TICK}{_BASE_COLOUR}'

    print((f'|{"".join(progress_bar)}|') + ['', f'{percentage}%'][annotation])
